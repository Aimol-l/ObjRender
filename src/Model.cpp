#include "Model.h"


void ren::Model::draw_model(Shader &shader){
    for(auto&mesh:m_meshes) mesh.draw_mesh(shader);
}

void ren::Model::load_model(const std::string &path){
    Assimp::Importer import;
    // const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);    
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    m_directory = path.substr(0, path.find_last_of('/'));
    process_node(scene->mRootNode, scene);
}

uint ren::Model::load_images(const std::string &name, const std::string &dir_path, bool gamma){
	auto file_path = name;
	uint textureID;
	glGenTextures(1, &textureID);
	int width, height, Channels;
    stbi_set_flip_vertically_on_load(false);
	u_char *data = stbi_load(file_path.c_str(), &width, &height, &Channels, 0);
	if (data){
		GLenum format;
		if (Channels == 1) format = GL_RED;
		if (Channels == 3) format = GL_RGB;
		if (Channels == 4) format = GL_RGBA;
 
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_image_free(data);
	}else{
		std::cout << "纹理无法从此路径加载: " << file_path << std::endl;
		stbi_image_free(data);
	}
	return textureID;
}

void ren::Model::process_node(aiNode *node, const aiScene *scene){
    // 处理位于当前节点的每个网格
    for (unsigned int i = 0; i < node->mNumMeshes; i++){
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(process_mesh(mesh, scene));
    }
    // 在我们处理完所有网格（如果有的话）后，我们会递归处理每个子节点
    for (unsigned int i = 0; i < node->mNumChildren; i++)
        process_node(node->mChildren[i], scene);
}

ren::Mesh ren::Model::process_mesh(aiMesh *mesh, const aiScene *scene){
    std::vector<Vertex> vertices;
    // 遍历每个网格的顶点
    for (uint i = 0; i < mesh->mNumVertices; i++){
        Vertex vertex;
        // 我们声明一个占位符向量，因为assimp使用它自己的向量类，它不直接转换为glm的vec3类，所以我们首先将数据传递给这个占位符glm :: vec3。
        vertex.Position = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};// 位置
        vertex.Normal = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};// 法线
        // 纹理坐标, // 网格是否包含纹理坐标？
        if (mesh->mTextureCoords[0]){
            // 顶点最多可包含8个不同的纹理坐标。 因此，我们假设我们不会使用顶点可以具有多个纹理坐标的模型，因此我们总是采用第一个集合（0）。
            vertex.TexCoords = {mesh->mTextureCoords[0][i].x,mesh->mTextureCoords[0][i].y};
        }else  vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        vertex.Tangent = {mesh->mTangents[i].x,mesh->mTangents[i].y,mesh->mTangents[i].z};// u向量
        vertex.Bitangent = {mesh->mBitangents[i].x,mesh->mBitangents[i].y,mesh->mBitangents[i].z};// v向量
        vertices.push_back(vertex);
    }
    std::vector<uint> indices;
    //现在遍历每个网格面（一个面是一个三角形的网格）并检索相应的顶点索引。
    for (uint i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        // 检索面的所有索引并将它们存储在索引向量中
        for (uint j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    std::vector<Texture> textures;
    if(mesh->mMaterialIndex >= 0){
        // 加工材质
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // 1. 漫反射贴图
        std::vector<Texture> diffuseMaps = load_textures(material, aiTextureType_DIFFUSE, TEXTYPE::TEXTURE_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. 高光贴图
        std::vector<Texture> specularMaps = load_textures(material, aiTextureType_SPECULAR, TEXTYPE::TEXTURE_SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3.法线贴图
        std::vector<Texture> normalMaps = load_textures(material, aiTextureType_HEIGHT,TEXTYPE::TEXTURE_NORMAL);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. 高度贴图
        std::vector<Texture> heightMaps = load_textures(material, aiTextureType_AMBIENT, TEXTYPE::TEXTURE_HEIGHT);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
        // 返回从提取的网格数据创建的网格对象
    }
    return Mesh(vertices, indices, textures);
}

std::vector<ren::Texture> ren::Model::load_textures(aiMaterial *mat, aiTextureType type, TEXTYPE typeName){
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++){
        aiString str;
        mat->GetTexture(type, i, &str);
        // 检查之前是否加载了纹理，如果是，则继续下一次迭代：跳过加载新纹理
        bool skip = false;
        for (unsigned int j = 0; j < m_textures_loaded.size(); j++){
            if (std::strcmp(m_textures_loaded[j].path.data(), str.C_Str()) == 0){
                textures.push_back(m_textures_loaded[j]);
                skip = true; 
                break;// 已加载具有相同文件路径的纹理，继续下一个（优化）。
            }
        }
        if (!skip){   // 如果尚未加载纹理，请加载它
            Texture texture;
            texture.id = load_images(str.C_Str(), this->m_directory,false);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            m_textures_loaded.push_back(texture);  //将其存储为整个模型加载的纹理，以确保我们不会加载重复纹理。
        }
    }
    return textures;
}

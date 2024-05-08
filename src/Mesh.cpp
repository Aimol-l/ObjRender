#include "Mesh.h"
ren::Mesh::Mesh(std::vector<Vertex> &vertexs, std::vector<uint> &indices, std::vector<Texture> &textutes){
    this->m_indices = indices;
    this->m_textures = textutes;
    this->m_vertices = vertexs;
    this->init_mesh();
}
void ren::Mesh::init_mesh(){
     //******************************VAO**************************
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    //******************************VBO***************************
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);  
    // 顶点位置VBO
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // 顶点法线VBO
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // 纹理坐标VBO
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // 顶点切线VBO
    glEnableVertexAttribArray(3);	
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // 顶点双切VBO
    glEnableVertexAttribArray(4);	
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    // // ids VBO
    // glEnableVertexAttribArray(5);
    // glVertexAttribIPointer(5, MAX_BONE_INFLUENCE, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));
    // // weights VBO
    // glEnableVertexAttribArray(6);
    // glVertexAttribPointer(6, MAX_BONE_INFLUENCE, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
    //*****************************EBO**************************************
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(),GL_STATIC_DRAW);
    //********************************解绑VAO,EBO****************************
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void ren::Mesh::draw_mesh(Shader &shader){
    // bind appropriate textures
    uint diffuseNr  = 1;
    uint specularNr = 1;
    uint normalNr   = 1;
    uint heightNr   = 1;
    for(size_t i = 0; i < m_textures.size(); i++){
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name;
        if(m_textures[i].type == TEXTYPE::TEXTURE_DIFFUSE){
            number = std::to_string(diffuseNr++);
            name = "texture_diffuse";
        }else if((m_textures[i].type == TEXTYPE::TEXTURE_SPECULAR)){
            number = std::to_string(specularNr++); // transfer unsigned int to string]
            name = "texture_specular";
        }else if((m_textures[i].type == TEXTYPE::TEXTURE_NORMAL)){
            number = std::to_string(normalNr++); // transfer unsigned int to string
            name = "texture_normal";
        }else if((m_textures[i].type == TEXTYPE::TEXTURE_HEIGHT)){
            number = std::to_string(heightNr++); // transfer unsigned int to string
            name = "texture_height";
        }
        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader.get_id(), (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
    }
    // draw mesh
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, static_cast<uint>(m_indices.size()), GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

#pragma once

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC


#include "Mesh.h"
#include "Shader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "stb_image.h"
namespace ren{
class Model {
public:
    Model(){};
    Model(const std::string &path) {
        load_model(path);
    }
    Model(const std::string &path,const glm::vec3 model_pos) {
        load_model(path);
        m_pos = model_pos;
    } 
    void load_model(const std::string &path);
    void draw_model(Shader &shader); 
    glm::mat4 get_mat();
private:
    glm::vec3 m_pos = {0.0f,0.0f,0.0f};
    // glm::vec3 m_scale = {1.0f,1.0f,1.0f};
    std::string m_directory;
    std::vector<Mesh> m_meshes;
    std::vector<Texture> m_textures_loaded;

    void process_node(aiNode *node, const aiScene *scene);
    Mesh process_mesh(aiMesh *mesh, const aiScene *scene);
    uint load_images(const std::string &path, const std::string &directory, bool gamma);
    std::vector<Texture> load_textures(aiMaterial *mat, aiTextureType type, TEXTYPE typeName);
};
}
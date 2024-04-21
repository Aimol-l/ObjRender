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

class Model {
public:
    Model(){};
    Model(std::string &path) {load_model(path);} 
    void load_model(std::string &path);
    void draw_model(Shader &shader); 
private:
    std::string m_directory;
    std::vector<Mesh> m_meshes;
    std::vector<Texture> m_textures_loaded;

    void process_node(aiNode *node, const aiScene *scene);
    Mesh process_mesh(aiMesh *mesh, const aiScene *scene);
    uint load_images(const std::string &path, const std::string &directory, bool gamma);
    std::vector<Texture> load_textures(aiMaterial *mat, aiTextureType type, TEXTYPE typeName);
};
#pragma once
#include <glad/glad.h>
#include "glm/glm.hpp"
#include <iostream>
#include <vector>
#include "Shader.h"

// constexpr static uint MAX_BONE_INFLUENCE = 4;

enum class TEXTYPE{
    TEXTURE_DIFFUSE, //漫反射纹理贴图
    TEXTURE_SPECULAR, //镜面反射纹理贴图
    TEXTURE_NORMAL, // 法线纹理贴图
    TEXTURE_HEIGHT // 高度纹理贴图
};
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};
struct Texture {
    uint id;
    TEXTYPE type;
    std::string path;
};
class Mesh {
private:
    uint m_vbo,m_ebo;
    std::vector<uint> m_indices;
    std::vector<Vertex> m_vertices;
    std::vector<Texture> m_textures;

    //将顶点，纹理，索引加载到gpu中
    void init_mesh();
public:
    uint m_vao;
    //绘制的时候需要知道有多少种类型，分别是什么类型的纹理
    void draw_mesh(Shader &shader);
    Mesh(std::vector<Vertex>&, std::vector<uint>&, std::vector<Texture>&);
};  
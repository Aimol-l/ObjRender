#pragma once
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb_image.h"
#include <iostream>
#include <glad/glad.h>
#include <vector>
#include <array>
#include <format>
#include "glm/glm.hpp"
//负责纹理的加载、生成和管理。这个类可以包含纹理的ID、尺寸、格式等信息。
class Texture{
private:
    size_t m_size = 0;
    GLuint m_id;
    glm::vec3 m_dim;
    unsigned char * m_image;
public:
    Texture();
    ~Texture();
    void log_texture(const std::string& filePath);
    void  bind();
    void unbind() const;
};
  
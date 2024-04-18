#include "Texture.h"

Texture::Texture(){
}

Texture::~Texture(){
    
}
void Texture::log_texture(const std::string &filePath){
    stbi_set_flip_vertically_on_load(true);
    int width, height, Channels;
    unsigned char *image = stbi_load(filePath.c_str(), &width, &height, &Channels, 0);
    if (!image) {
        std::cout << "Failed to load image: " << filePath << std::endl;
        return;
    }
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    this->m_dim = {width,height,Channels};
    GLenum format;
    if (Channels == 3)  format = GL_RGB;
    if (Channels == 4)  format = GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_dim.x, m_dim.y, 0, format, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);
}
void Texture::bind(){
    glBindTexture(GL_TEXTURE_2D, m_id);
}
void Texture::unbind() const{
    glBindTexture(GL_TEXTURE_2D, 0);
}

#include "Texture.h"

Texture::Texture(){
}

Texture::~Texture(){
    
}
void Texture::log_texture(const std::string &filePath){
    stbi_set_flip_vertically_on_load(true);
    int width, height, Channels;
    unsigned char *image = stbi_load(filePath.c_str(), &width, &height, &Channels, 0);
    // std::cout<<std::format("width = {}, height={}, Channels={}",width, height, Channels)<<std::endl;
    this->m_dim = {width,height,Channels};
    // this->m_image = image;
    if (image){
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_dim.x, m_dim.y, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout<<"Failed to load image!!!"<<std::endl;
    }
    stbi_image_free(image);
}
void Texture::bind(){
    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, m_id);
}
void Texture::unbind() const{
    glBindTexture(GL_TEXTURE_2D, 0);
}

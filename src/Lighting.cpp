#include "Lighting.h"
#include <glm/gtc/type_ptr.hpp>

//********************************************************
Lighting::~Lighting(){
    delete m_light_model;
}
Lighting::Lighting(int type=0,const std::string &model_path){
    m_light_model->load_model(model_path);
}

void Lighting::draw_light(Shader &shader,size_t index){
    std::string lightIndex = "lights[" + std::to_string(index) + "]";
    GLuint loc_ambient = glGetUniformLocation(shader.get_id(), (lightIndex + ".ambient").c_str());
    GLuint loc_diffuse = glGetUniformLocation(shader.get_id(), (lightIndex + ".diffuse").c_str());
    GLuint loc_specular = glGetUniformLocation(shader.get_id(), (lightIndex + ".specular").c_str());
    GLuint loc_position = glGetUniformLocation(shader.get_id(), (lightIndex + ".position").c_str());
    GLuint loc_direction = glGetUniformLocation(shader.get_id(), (lightIndex + ".direction").c_str());
    GLuint loc_type = glGetUniformLocation(shader.get_id(), (lightIndex + ".type").c_str());

    glUniform3fv(loc_ambient, 1, glm::value_ptr(m_ambient));
    glUniform3fv(loc_diffuse, 1, glm::value_ptr(m_diffuse));
    glUniform3fv(loc_specular, 1, glm::value_ptr(m_specular));
    glUniform3fv(loc_position, 1, glm::value_ptr(m_pos));
    glUniform3fv(loc_direction, 1, glm::value_ptr(m_direction));
    glUniform1i(loc_type, m_type);
}

void Lighting::init(glm::vec3 &pos, glm::vec3 &color){
    m_pos = pos;
    m_color = color;
}
void Lighting::init(glm::vec3 &pos,glm::vec3 &direction,glm::vec3 &color){
    m_pos = pos;
    m_color = color;
    m_direction = direction;
}
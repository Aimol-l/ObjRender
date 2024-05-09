#include "Lighting.h"
#include <glm/gtc/type_ptr.hpp>

//********************************************************
ren::Lighting::~Lighting(){
}
ren::Lighting::Lighting(int type,const std::string &model_path):m_type(type){
    m_light_model = std::make_unique<Model>();
    m_light_model->load_model(model_path);
}

void ren::Lighting::draw_light(Shader &shader,size_t index){
    std::string light_index = "lights[" + std::to_string(index) + "]";
    GLuint loc_type = glGetUniformLocation(shader.get_id(), (light_index + ".type").c_str());
    GLuint loc_position = glGetUniformLocation(shader.get_id(), (light_index + ".position").c_str());
    GLuint loc_direction = glGetUniformLocation(shader.get_id(), (light_index + ".direction").c_str());
    GLuint loc_color = glGetUniformLocation(shader.get_id(), (light_index + ".color").c_str());
    GLuint loc_ambient = glGetUniformLocation(shader.get_id(), (light_index + ".ambient").c_str());
    GLuint loc_diffuse = glGetUniformLocation(shader.get_id(), (light_index + ".diffuse").c_str());
    GLuint loc_specular = glGetUniformLocation(shader.get_id(), (light_index + ".specular").c_str());
    
    GLuint loc_constant = glGetUniformLocation(shader.get_id(), (light_index + ".constant").c_str());
    GLuint loc_linear = glGetUniformLocation(shader.get_id(), (light_index + ".linear").c_str());
    GLuint loc_quadratic = glGetUniformLocation(shader.get_id(), (light_index + ".quadratic").c_str());
    GLuint loc_cut_off = glGetUniformLocation(shader.get_id(), (light_index + ".cut_off").c_str());
    GLuint loc_outer_cut_off = glGetUniformLocation(shader.get_id(), (light_index + ".outer_cut_off").c_str());

    glUniform1i(loc_type, m_type);
    glUniform3fv(loc_position, 1, glm::value_ptr(m_pos));
    glUniform3fv(loc_direction, 1, glm::value_ptr(m_direction));
    glUniform3fv(loc_color, 1, glm::value_ptr(m_color));
    glUniform3fv(loc_ambient, 1, glm::value_ptr(m_ambient));
    glUniform3fv(loc_diffuse, 1, glm::value_ptr(m_diffuse));
    glUniform3fv(loc_specular, 1, glm::value_ptr(m_specular));

    glUniform1f(loc_constant, m_constant);
    glUniform1f(loc_linear, m_linear);
    glUniform1f(loc_quadratic, m_quadratic);
    glUniform1f(loc_cut_off, m_cut_off);
    glUniform1f(loc_outer_cut_off, m_outer_cut_off);
    //******************************设置光源位置**************************************
    auto now =  std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - create_time) / 1000000.0f;
    glm::vec3 new_pos = {5*glm::cos(duration.count()),0,5*glm::sin(duration.count())};
    this->set_pos(new_pos);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, m_pos);// 设置模型的位置
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));// 设置模型的缩放
    shader.set_mat4("modelMat",model);
    m_light_model->draw_model(shader);
}

void ren::Lighting::init(glm::vec3 &pos, glm::vec3 &color){
    m_pos = pos;
    m_color = color;
}
void ren::Lighting::init(glm::vec3 &pos,glm::vec3 &direction,glm::vec3 &color){
    m_pos = pos;
    m_color = color;
    m_direction = direction;
}
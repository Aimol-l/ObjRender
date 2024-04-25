#include "Lighting.h"


//********************************************************
Lighting::~Lighting(){
    delete m_light_model;
}
Lighting::Lighting(const std::string &model_path){
    m_light_model->load_model(model_path);
}
void Lighting::set_ratio(float amb, float diff, float spe){

}
//********************************************************
void ParallelLight::draw_light(Shader &shader){
    glUniform3f(glGetUniformLocation(shader.get_id(),"lightPos"),m_pos.x,m_pos.y,m_pos.z);
    glUniform3f(glGetUniformLocation(shader.get_id(),"lightColor"),m_color.x,m_color.y,m_color.z);
    glUniform3f(glGetUniformLocation(shader.get_id(),"lightDirection"),m_color.x,m_color.y,m_color.z);
    m_light_model->draw_model(shader);
}
void ParallelLight::set_parmas(const glm::vec3 &pos,const glm::vec3 &color, const glm::vec3 & dire){
    m_pos = pos;
    m_color = color;
    m_direction = dire;
}
//********************************************************

//********************************************************





//********************************************************
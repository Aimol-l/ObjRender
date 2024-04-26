#include "Render.h"
#include "Event.h"
#include "Log.h"

void check_error(std::string info){
    GLenum  error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error after"<< info << error << std::endl;
    }
}
Render::Render(){
    m_camera = Camera::get_instence();
    m_shader = new Shader();
    m_model = new Model();
};
Render::~Render(){
    delete m_camera,m_shader,m_model;
}
void Render::add_shader(const std::string &vertex_path, const std::string &fragment_path){
    Log::info("add_shader....");
    Log::info("vertex_path = "+vertex_path);
    Log::info("fragment_path = "+fragment_path);
    m_shader->create_shader(vertex_path,fragment_path);
    m_shader->use();
    Log::info("add_shader....done!!");
}

void Render::add_light(Lighting* temp){
    if(temp != nullptr) m_lights.push_back(temp);
}

void Render::add_model(const std::string& model_path){
    Log::info("add_model....");
    m_model->load_model(model_path);
    Log::info("add_model....done!!");
}
void Render::add_camera(glm::vec3 &pos, glm::vec3 &forward, glm::vec3 &up){
    Log::info("add_camera....");
    m_camera->set_position(pos);
    m_camera->set_forward(forward);
    m_camera->set_up(up);
    m_camera->set_rotation(0,180,0);
    Log::info("add_camera....done!!");
}

glm::mat4x4 Render::get_view(){
    return m_camera->get_view_mat();
}

//绘制上所有的mesh,lamp
void Render::draw(){
    m_model->draw_model(*m_shader);
    for(auto*light:m_lights) light->draw_light(*m_shader);
}

void Render::set_shader(const std::string &name, int val) const
{
    glUniform1i(glGetUniformLocation(m_shader->get_id(), name.c_str()), val ? 1 : 0);
}

void Render::set_shader(const std::string &name, bool val) const{
     glUniform1i(glGetUniformLocation(m_shader->get_id(), name.c_str()), val);
}

void Render::set_shader(const std::string &name, float val) const{
    glUniform1f(glGetUniformLocation(m_shader->get_id(), name.c_str()), val);
}

void Render::set_shader(const std::string &name, glm::vec3 &vec) const{
    glUniform4f(glGetUniformLocation(m_shader->get_id(),name.c_str()),vec.x,vec.y,vec.z,0);
}

void Render::set_shader(const std::string &name, glm::vec4 &vec) const{
    glUniform4f(glGetUniformLocation(m_shader->get_id(),name.c_str()),vec.x,vec.y,vec.z,vec.w);
}

void Render::set_shader(const std::string &name, const glm::mat2 &mat) const{
    glUniformMatrix4fv(glGetUniformLocation(m_shader->get_id(),name.c_str()),1,GL_FALSE,&mat[0][0]);
}

void Render::set_shader(const std::string &name, const glm::mat3 &mat) const{
    glUniformMatrix4fv(glGetUniformLocation(m_shader->get_id(),name.c_str()),1,GL_FALSE,&mat[0][0]);
}

void Render::set_shader(const std::string &name, const glm::mat4 &mat) const{
    glUniformMatrix4fv(glGetUniformLocation(m_shader->get_id(),name.c_str()),1,GL_FALSE,&mat[0][0]);
}
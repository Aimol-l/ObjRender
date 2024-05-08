#include "Render.h"
#include "Log.h"

void check_error(std::string info){
    GLenum  error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error after"<< info << error << std::endl;
    }
}
Render::Render(){
    m_camera = std::make_unique<Camera>(Camera::get_instence());
};
Render::~Render(){}
void Render::add_shader(const std::string &vertex_path, const std::string &fragment_path){
    Log::info("add_shader....");
    Log::info("vertex_path = "+vertex_path);
    Log::info("fragment_path = "+fragment_path);
    m_shader = std::make_unique<Shader>(vertex_path,fragment_path);
    m_shader->use();
    Log::info("add_shader....done!!");
}

void Render::add_light(std::unique_ptr<Lighting>&light){
    m_lights.push_back(std::move(light));
    GLuint loc_num = glGetUniformLocation(m_shader->get_id(), "num_light");
    glUniform1i(loc_num, static_cast<int>(m_lights.size()));
}
void Render::add_model(const std::string& model_path){
    Log::info("add_model....");
    m_model = std::make_unique<Model>(model_path);
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
//绘制上所有的mesh,lamp
void Render::draw(){
    glm::mat4 modelMat = m_camera->get_scale() * glm::mat4(1.0f);
    glm::mat4 projectMat = glm::perspective(glm::radians(45.0f),1024.0f / 800.0f, 0.1f, 100.0f);
    glm::mat4 viewMat = m_camera->get_view_mat();
    auto camera_pos = m_camera->get_position();
    //给shader设置MVP矩阵
    this->set_shader("modelMat",modelMat);
    this->set_shader("projectMat",projectMat);
    this->set_shader("viewMat",viewMat);
    this->set_shader("camera_pos",camera_pos);
    m_model->draw_model(*m_shader);
    for(size_t index;index<m_lights.size();++index) 
        m_lights[index]->draw_light(*m_shader,index);

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
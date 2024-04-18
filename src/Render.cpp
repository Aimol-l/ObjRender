#include "Render.h"
#include "Event.h"
#include "Log.h"

void check_error(std::string info){
    GLenum  error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error after"<< info << error << std::endl;
    }
}

void Render::add_obj(const std::string &obj_path, const std::string &texture_path){
    m_obj->load_obj(obj_path);
    m_texture->log_texture(texture_path);
    Log::info("obj model file path: "+obj_path);
    Log::info("texture file path: "+texture_path);
    //*******************************************************************
    auto vertices = m_obj->get_vertexes();
    for(const auto&v:vertices){
        std::cout<<std::format("[{},{},{}]",v.x,v.y,v.z)<<std::endl;
    }
    std::cout<<std::format("*************")<<std::endl;
    auto textures = m_obj->get_ver_texture();
    for(const auto&t:textures){
        std::cout<<std::format("[{},{}]",t.x,t.y)<<std::endl;
    }
    std::cout<<std::format("*************")<<std::endl;
    auto normals = m_obj->get_ver_normals();
    for(const auto&n:normals){
        std::cout<<std::format("[{},{},{}]",n.x,n.y,n.z)<<std::endl;
    }
    std::cout<<std::format("*************")<<std::endl;
    auto faces = m_obj->get_faces();
    std::vector<uint> EBO;
    // EBO.resize(faces.size()*8);
    for(auto const &f: faces) {
        for(int i =0;i<3;++i) EBO.push_back(f.v.at(i));
        // for(int i =0;i<2;++i) EBO.push_back(f.vt.at(i));
        // for(int i =0;i<3;++i) EBO.push_back(f.vn.at(i));
    }
    for(auto const &f: faces) {
        // for(int i =0;i<3;++i) EBO.push_back(f.v.at(i));
        for(int i =0;i<2;++i) EBO.push_back(f.vt.at(i));
        // for(int i =0;i<3;++i) EBO.push_back(f.vn.at(i));
    }
    for(auto const &f: faces) {
        // for(int i =0;i<3;++i) EBO.push_back(f.v.at(i));
        // for(int i =0;i<2;++i) EBO.push_back(f.vt.at(i));
        for(int i =0;i<3;++i) EBO.push_back(f.vn.at(i));
    }
    //******************************VAO*************************************
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    //******************************顶点位置坐标VBO***************************
    GLuint temp_vbo1;
    glGenBuffers(1, &temp_vbo1);
    m_VBOs.push_back(temp_vbo1);
    glBindBuffer(GL_ARRAY_BUFFER, temp_vbo1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size() , &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(glm::vec3), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    check_error("temp_vbo1");
    //******************************顶点纹理坐标VBO**************************
    GLuint temp_vbo2;
    glGenBuffers(1, &temp_vbo2);
    m_VBOs.push_back(temp_vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, temp_vbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * textures.size(), &textures[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    check_error("temp_vbo2");
    //******************************顶点法线向量VBO*************************************
    GLuint temp_vbo3;
    glGenBuffers(1, &temp_vbo3);
    m_VBOs.push_back(temp_vbo3);
    glBindBuffer(GL_ARRAY_BUFFER, temp_vbo3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), &normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    check_error("temp_vbo3");
    //*****************************EBO**************************************
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * EBO.size(), EBO.data(), GL_STATIC_DRAW);

    // GLuint temp_ebo2;
    // glGenBuffers(1, &temp_ebo2);
    // m_EBOs.push_back(temp_ebo2);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, temp_ebo2);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * EBO2.size(), EBO2.data(), GL_STATIC_DRAW);

    // GLuint temp_ebo3;
    // glGenBuffers(1, &temp_ebo3);
    // m_EBOs.push_back(temp_ebo3);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, temp_ebo3);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * EBO3.size(), EBO3.data(), GL_STATIC_DRAW);
    //*******************************************************************
    // 解绑VAO,EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    check_error("done!!");
}
void Render::bind(){
    m_texture->bind();
    glBindVertexArray(m_vao);
}
void Render::unbind(){
    glBindVertexArray(0);
    m_texture->unbind();
}
Render::Render(){
    m_camera = Camera::get_instence();
    m_obj = new ObjLoader();
    m_shader = new Shader();
    m_texture = new Texture();
};
Render::~Render(){
    delete m_camera,m_obj,m_shader;
    glDeleteVertexArrays(1, &m_vao);
    glDeleteVertexArrays(1, &m_ebo);
    for(size_t i =0 ; i<m_VBOs.size();i++)  glDeleteBuffers(1, &m_VBOs[i]);
}
void Render::add_shader(const std::string &vertex_path, const std::string &fragment_path){
    Log::info("add_shader....");
    Log::info("vertex_path = "+vertex_path);
    Log::info("fragment_path = "+fragment_path);
    m_shader->create_shader(vertex_path,fragment_path);
    m_shader->use();
    Log::info("add_shader....done!!");
}
void Render::add_lighting(){

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

void Render::set_shader(const std::string &name, int val) const{
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
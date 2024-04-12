#pragma once

#include "glm/glm.hpp"
#include "ObjLoader.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "Event.h"
class Render{
private:
    ObjLoader* m_obj = nullptr;
    Camera* m_camera = nullptr;
    Shader* m_shader = nullptr;
    Texture* m_texture = nullptr;
    std::vector<GLuint> m_VBOs;
    GLuint m_vao,m_ebo;
public:
    Render();
    ~Render();
    glm::mat4x4 get_view();
    void set_shader(const std::string &name,int val)const;
    void set_shader(const std::string &name,bool val)const;
    void set_shader(const std::string &name,float val)const;
    void set_shader(const std::string &name,glm::vec3 &vec)const;
    void set_shader(const std::string &name,glm::vec4 &vec)const;
    void set_shader(const std::string &name,const glm::mat2 &mat)const;
    void set_shader(const std::string &name,const glm::mat3 &mat)const;
    void set_shader(const std::string &name,const glm::mat4 &mat)const;

    void add_lighting();
    void add_camera(glm::vec3& pos,glm::vec3 &forward,glm::vec3 &up);
    void add_shader(const std::string &vertex_path,const std::string &fragment_path);
    void add_obj(const std::string& obj_path,const std::string& texture_path);

    inline size_t get_num_faces() { return m_obj->get_num_faces();};
    inline size_t get_num_v(){return m_obj->get_num_v();};
    inline size_t get_num_vn(){return m_obj->get_num_vn();};
    inline size_t get_num_vt(){return m_obj->get_num_vt();};

    void bind();
    void unbind();

};

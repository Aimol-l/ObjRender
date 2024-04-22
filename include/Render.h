#pragma once

#include "glm/glm.hpp"
#include "Camera.h"
#include "Shader.h"
#include "Event.h"
#include "Model.h"
class Render{
private:
    Camera* m_camera = nullptr;
    Shader* m_shader = nullptr;
    Model* m_model = nullptr;
public:
    Render();
    ~Render();
    glm::mat4x4 get_view();

    void draw();

    void set_shader(const std::string &name,int val)const;
    void set_shader(const std::string &name,bool val)const;
    void set_shader(const std::string &name,float val)const;
    void set_shader(const std::string &name,glm::vec3 &vec)const;
    void set_shader(const std::string &name,glm::vec4 &vec)const;
    void set_shader(const std::string &name,const glm::mat2 &mat)const;
    void set_shader(const std::string &name,const glm::mat3 &mat)const;
    void set_shader(const std::string &name,const glm::mat4 &mat)const;

    void add_model(std::string model_path);
    void add_camera(glm::vec3& pos,glm::vec3 &forward,glm::vec3 &up);
    void add_shader(const std::string &vertex_path,const std::string &fragment_path);

};

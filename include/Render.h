#pragma once

#include "glm/glm.hpp"
#include "Camera.h"
#include "Shader.h"
#include "Model.h"
#include "Lighting.h"
namespace ren{
class Render{
private:
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<Shader> m_shader;
    std::vector<std::unique_ptr<Model>> m_models;
    // std::unique_ptr<Model> m_model;
    std::vector<std::unique_ptr<Lighting>> m_lights;
public:
    Render();
    ~Render();

    void draw();
    void set_shader(const std::string &name,int val)const;
    void set_shader(const std::string &name,bool val)const;
    void set_shader(const std::string &name,float val)const;
    void set_shader(const std::string &name,glm::vec3 &vec)const;
    void set_shader(const std::string &name,glm::vec4 &vec)const;
    void set_shader(const std::string &name,const glm::mat2 &mat)const;
    void set_shader(const std::string &name,const glm::mat3 &mat)const;
    void set_shader(const std::string &name,const glm::mat4 &mat)const;

    void add_light(std::unique_ptr<Lighting>&light);
    void add_model(const std::string &model_path);
    void add_model(const std::string &model_path,const glm::vec3& model_pos);
    void add_camera(glm::vec3& pos,glm::vec3 &forward,glm::vec3 &up);
    void add_shader(const std::string &vertex_path,const std::string &fragment_path);

};
}
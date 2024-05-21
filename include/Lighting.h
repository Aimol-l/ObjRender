#pragma once
#include <glad/glad.h>
#include "glm/glm.hpp"
#include "Shader.h"
#include "Model.h"
#include <chrono>
#include "Camera.h"

namespace ren{
class Lighting{
protected:
    int m_type = 0; //{0:平行光, 1:点光源, 2:聚光灯}
    glm::vec3 m_pos = {0.0f,3.0f,0.0f}; //光源位置
    glm::vec3 m_direction = {0.0f,10.0f,0.0f};//光源方向
    glm::vec3 m_color = {1.0f,1.0f,1.0f}; //光源颜色

    glm::vec3 m_ambient =    {0.4f, 0.4f, 0.4f};  //环境光强系数
    glm::vec3 m_diffuse =   {1.0f, 1.0f, 1.0f};     //漫反射系数
    glm::vec3 m_specular =  {1.0f, 1.0f, 1.0f};     //镜面反射系数

    float m_constant = 1.0f;    //常数
    float m_linear = 0.1f;     //一次项衰减系数
    float m_quadratic = 0.05f; //二次项衰减系数

    float m_cut_off = glm::pi<float>()/18.0f;    //聚光登范围1,弧度单位
    float m_outer_cut_off = glm::pi<float>()/12.0f; //聚光灯范围2,弧度单位

    std::chrono::system_clock::time_point create_time = std::chrono::system_clock::now();;
    std::unique_ptr<Model> m_light_model;
private:
     void set_type(int type){m_type = type;}
     void set_pos(glm::vec3& pos){ m_pos = pos;}
     void set_direction(glm::vec3& direction){ m_direction = direction;}
     void set_color(glm::vec3& color){ m_color = color;}
public:
     void set_ambient(glm::vec3& ambient){ m_ambient = ambient;}
     void set_diffuse(glm::vec3& diffuse){ m_diffuse = diffuse;}
     void set_specular(glm::vec3& specular){ m_specular = specular;}
     void set_constant(float constant){ m_constant = constant;}
     void set_linear(float linear){ m_linear = linear;}
     void set_quadratic(float quadratic){ m_quadratic = quadratic;}
     void set_cut_off(float cut_off){ m_cut_off = cut_off*glm::pi<float>()/180.0f;}
     void set_outer_cut_off(float outer_cut_off){ m_outer_cut_off = outer_cut_off*glm::pi<float>()/180.0f;}
public:
    ~Lighting();
    //{0:平行光, 1:点光源, 2:聚光灯}
    Lighting(int type,const std::string & model_path);
    void draw_light(Shader &shader,size_t index);
    //平行光
     void init(glm::vec3&,glm::vec3&);
    //点光源,聚光灯
     void init(glm::vec3&,glm::vec3&,glm::vec3&);
};
}
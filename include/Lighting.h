#pragma once
#include "glm/glm.hpp"
#include "Shader.h"
#include "Model.h"

class Lighting{
protected:
    int m_type = 0; //{0:平行光, 1:点光源, 2:聚光灯}
    glm::vec3 m_pos = {0.0f,5.0f,0.0f}; //光源位置
    glm::vec3 m_direction = {0.0f,0.0f,0.0f};//光源方向
    glm::vec3 m_color = {1.0f,1.0f,1.0f}; //光源颜色

    glm::vec3 m_ambient =    {0.05f, 0.05f, 0.05f};  //环境光强系数
    glm::vec3 m_diffuse =   {0.8f, 0.8f, 0.8f};     //漫反射系数
    glm::vec3 m_specular =  {1.0f, 1.0f, 1.0f};     //镜面反射系数

    float m_constant = 1.0f;    //常数
    float m_linear = 0.09f;     //一次项衰减系数
    float m_quadratic = 0.032f; //二次项衰减系数
    float m_cut_off = 12.5f;    //聚光登范围1
    float m_outer_cut_off = 15.0f; //聚光灯范围2
    Model* m_light_model = nullptr;
public:
    ~Lighting();
    //{0:平行光, 1:点光源, 2:聚光灯}
    Lighting(int type = 0,const std::string & model_path);
    void draw_light(Shader &shader);
    
    void init_parallel(int,);
    void init_pint();
    void init_spot();
};

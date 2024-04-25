#pragma once
#include "glm/glm.hpp"
#include "Shader.h"
#include "Model.h"

class Lighting{
protected:
    glm::vec3 m_pos = {0.0f,5.0f,0.0f};
    glm::vec3 m_color = {1.0f,1.0f,1.0f};
    float m_ambient_ratio = 0.1f;
    float m_diffuse_ratio = 0.5f;
    float m_specular_ratio = 1.0f;
    Model* m_light_model = nullptr;
public:
    Lighting(const std::string & model_path);
    virtual ~Lighting();
    virtual void draw_light(Shader &shader) = 0;

    void set_ratio(float amb,float diff,float spe);
};
// 平行光，考虑距离因素
class ParallelLight:public Lighting{
private:
    glm::vec3 m_direction = {0,0,0};
public:
    void draw_light(Shader &shader);
    void set_parmas(const glm::vec3&,const glm::vec3&,const glm::vec3&);
    ParallelLight(const std::string & model_path) :Lighting(model_path){}
};
// 聚光灯，类似点光
class SpotLight:public Lighting{
private:

public:

};

// 点光源，要考虑距离衰减效应
class PointLight:public Lighting{
private:

public:

};

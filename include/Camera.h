#pragma once
#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Log.h"
#include <iostream>

namespace ren{

class Camera{
private:
    glm::vec3 m_up; //上方向
    glm::vec3 m_position; //相机位置
    glm::vec3 m_rotation;
    glm::vec3 m_forward; //相机看的方向
    Camera() = default; 
public:
    ~Camera(){};
    Camera(const Camera *g) = delete; //拷贝构造函数
    Camera* operator=(const Camera *g) = delete; //赋值构造函数
    static Camera* get_instence(){
        static Camera* instance = new Camera(); 
        return instance;
    }
    glm::mat4x4 get_view_mat();
    glm::vec3 get_position();
    glm::vec3 get_direction();
    
    void set_up(glm::vec3 pos);
    void set_position(glm::vec3 pos);
    void set_forward(glm::vec3 pos);
    void translate(float x, float y, float z);
    void rotate(float pitch,float yaw,float roll );
    void set_rotation(float pitch,float yaw,float roll);
};
   
}
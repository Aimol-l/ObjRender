#include "Camera.h"


// 用于管理相机的位置、方向和投影矩阵。这个类可能包含相机的视角、投影类型（透视或正交）等属性，以及处理用户输入来控制相机的方法。

void ren::Camera::rotate(float pitch, float yaw, float roll){
    this->set_rotation(m_rotation.x+pitch,m_rotation.y+yaw,m_rotation.z+roll);
}

void ren::Camera::translate(float x, float y, float z){
    this->m_position += this->m_forward*z;
    this->m_position += glm::cross(this->m_forward,this->m_up) * x;
    this->m_position += this->m_up * y;
}
void ren::Camera::set_forward(glm::vec3 pos){
    this->m_forward = pos;
}
glm::mat4x4 ren::Camera::get_view_mat(){
    glm::mat4 viewMat =  glm::lookAt(m_position, m_position + m_forward, m_up);
    return  viewMat;
}
glm::vec3 ren::Camera::get_position(){
    return m_position;
}
// glm::mat4 ren::Camera::get_scale(){
//     glm::mat4 ret;
// 	ret = glm::transpose(glm::mat4(
//         m_scale.x, 0, 0, 0,
//         0, m_scale.y, 0, 0,
//         0, 0, m_scale.z, 0,
//         0, 0, 0, 1
//     ));
// 	return ret;
// }
// void ren::Camera::set_scale(double xoffset, double yoffset){
//     m_scale.x += yoffset * 0.05;
//     m_scale.y += yoffset * 0.05; 
//     m_scale.z = 1;
// }
void ren::Camera::set_up(glm::vec3 pos){
    this->m_up = pos;
}
void ren::Camera::set_position(glm::vec3 pos){
    this->m_position = pos;
    // std::cout<<std::format("set_position = [{:.2f},{:.2f},{:.2f}]",m_position.x,m_position.y,m_position.z)<<std::endl;
}
void ren::Camera::set_rotation(float pitch, float yaw, float roll){
    this->m_rotation = {pitch,yaw,roll};
    pitch  = pitch * M_PI/180.0f;
    yaw = yaw *M_PI/180.0f;
    this->m_forward = {glm::cos(pitch)*glm::sin(yaw),glm::sin(pitch),glm::cos(pitch)*glm::cos(yaw)};
    this->m_forward = glm::normalize(this->m_forward);
}

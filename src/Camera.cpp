#include "Camera.h"


// 用于管理相机的位置、方向和投影矩阵。这个类可能包含相机的视角、投影类型（透视或正交）等属性，以及处理用户输入来控制相机的方法。

void Camera::rotate(float pitch, float yaw, float roll){
    this->set_rotation(m_rotation.x+pitch,m_rotation.y+yaw,m_rotation.z+roll);
}
void Camera::translate(float x, float y, float z){
    this->m_position += this->m_forward*z;
    this->m_position += glm::cross(this->m_forward,this->m_up) * x;
    this->m_position += this->m_up * y;
    // std::cout<<std::format("m_position = [{:.2f},{:.2f},{:.2f}]",m_position.x,m_position.y,m_position.z)<<std::endl;
    // std::cout<<std::format("m_forward = [{:.2f},{:.2f},{:.2f}]",m_forward.x,m_forward.y,m_forward.z)<<std::endl;
    // std::cout<<std::format("m_up = [{:.2f},{:.2f},{:.2f}]",m_up.x,m_up.y,m_up.z)<<std::endl;
}
void Camera::set_forward(glm::vec3 pos){
    this->m_forward = pos;
    // std::cout<<std::format("set_forward=[{},{},{}]",m_forward.x,m_forward.y,m_forward.z)<<std::endl;
}
glm::mat4x4 Camera::get_view_mat(){
    glm::mat4 viewMat =  glm::lookAt(m_position, m_position + m_forward, m_up);
    return  viewMat;
}
glm::vec3 Camera::get_position(){
    return m_position;
}
void Camera::set_up(glm::vec3 pos)
{
    this->m_up = pos;
}
void Camera::set_position(glm::vec3 pos){
    this->m_position = pos;
    // std::cout<<std::format("set_position = [{:.2f},{:.2f},{:.2f}]",m_position.x,m_position.y,m_position.z)<<std::endl;
}
void Camera::set_rotation(float pitch, float yaw, float roll){
    this->m_rotation = {pitch,yaw,roll};
    pitch  = pitch * M_PI/180.0f;
    yaw = yaw *M_PI/180.0f;
    this->m_forward = {glm::cos(pitch)*glm::sin(yaw),glm::sin(pitch),glm::cos(pitch)*glm::cos(yaw)};
    this->m_forward = glm::normalize(this->m_forward);
}

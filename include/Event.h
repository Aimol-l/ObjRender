#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "Camera.h"

static Camera* CAMERA = Camera::get_instence();
// std::shared_ptr<Camera> CAMERA;
//这个类负责处理：鼠标移动事件，鼠标点击事件，键盘事件
void mouse_moveBack(GLFWwindow* window, double xpos, double ypos);
void mouse_clickBack(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
#pragma once
#include "Camera.h"
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <array>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


namespace ren{
//这个类是主窗口
class Window{
private:
    static ren::Camera* m_camera;;
    GLFWwindow* m_window;
    std::array<uint,2> m_size{0,0}; //w,h
    static bool m_pressed; 
    static glm::vec2 LASTPOS;
    static float SPEED;
public:
    Window();
    ~Window();
    bool close();
	void update();
    std::array<uint,2> get_size(){return m_size;};
    bool create_window(uint w, uint h, const char *title, bool is_full);

    // 初始化imgui的基本信息
    void init_imgui();
    // 不断重复渲染imgui
    void render_imgui();
    static void mouse_moveBack(GLFWwindow* window, double xpos, double ypos);
    static void mouse_clickBack(GLFWwindow* window, int button, int action, int mods);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

}
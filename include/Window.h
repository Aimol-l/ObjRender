#pragma once
#include "Camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <array>
//这个类是主窗口
class Window{
private:
    static std::unique_ptr<Camera> m_camera;
    std::unique_ptr<GLFWwindow> m_window = nullptr;
    std::array<uint,2> m_size{0,0}; //w,h
    static bool m_pressed; 
    static glm::vec2 LASTPOS;
    static float SPEED;
public:
    Window();
    ~Window();
    int close();
	void update() const;
    std::array<uint,2> get_size(){return m_size;};
    bool create_window(uint w, uint h, const char *title, bool is_full);

    static void mouse_moveBack(GLFWwindow* window, double xpos, double ypos);
    static void mouse_clickBack(GLFWwindow* window, int button, int action, int mods);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};


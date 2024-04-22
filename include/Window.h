#pragma once
#include "Event.h"
#include <iostream>
#include <array>
//这个类是主窗口
class Window{
private:
    GLFWwindow* m_window = nullptr;
    std::array<uint,2> m_size{0,0}; //w,h
public:
    Window();
    ~Window();
    int close();
	void update() const;
    std::array<uint,2> get_size(){return m_size;};
    bool create_window(uint w, uint h, const char *title, bool is_full);
};


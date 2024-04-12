#pragma once
#include "Event.h"
#include <iostream>
#include <array>
//这个类是主窗口
class Window{
private:
    GLFWwindow* m_window = nullptr;
    std::array<unsigned int,2> m_size{0,0}; //w,h
    void terminate() const;
public:
    Window();
    ~Window(){ this->terminate();};
    int close();
	void update() const;
    std::array<uint,2> get_size(){return m_size;};
    bool create_window(unsigned int w, unsigned int h, const char *title, bool is_full);
};


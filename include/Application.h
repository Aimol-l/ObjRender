#pragma once
#include "Window.h"
#include "Render.h"


class Application{
private:
    static Application* m_instance ; //静态成员    
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Render> m_render;
    Application() = default; //默认构造函数
public:
    ~Application();
    static Application &getApp(); // 获取单例对象
    Application(const Application & g) = delete; //拷贝构造函数
    Application& operator=(const Application & g) = delete; //赋值构造函数

    void run();
    void set_window(Window * win);
    void set_render(Render * rend);
};
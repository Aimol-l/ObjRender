#pragma once
#include "Window.h"
#include "Render.h"

namespace ren{

class Application{
private:
    static Application* m_instance ; //静态成员    
    std::unique_ptr<ren::Window> m_window;
    std::unique_ptr<ren::Render> m_render;
    Application() = default; //默认构造函数
public:
    ~Application();
    static ren::Application &get_app(); // 获取单例对象
    Application(const Application & g) = delete; //拷贝构造函数
    Application& operator=(const Application & g) = delete; //赋值构造函数

    void run();
    void set_window(std::unique_ptr<Window>& win);
    void set_render(std::unique_ptr<Render>& rend);
};

}
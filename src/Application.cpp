#include "Application.h"
#include "Log.h"
Application::~Application(){

}

Application &Application::getApp(){
    static Application m_instance; // singleton
	return m_instance;
}

void Application::run(){
    glEnable(GL_DEPTH_TEST);
    while (!this->m_window->close()){
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        
        m_render->draw();
        m_window->update();
    }
}

void Application::set_window(std::unique_ptr<Window>& win){ 
    m_window = std::move(win);
    Log::info("set_window done!!");
}

void Application::set_render(std::unique_ptr<Render>&rend){
    m_render = std::move(rend);
    Log::info("set_render done!!");
}
#include "Application.h"
#include "Log.h"
Application::~Application(){
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
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
        glm::mat4 modelMat = glm::mat4(1.0f);
        glm::mat4 projectMat = glm::perspective(glm::radians(45.0f),1024.0f / 800.0f, 0.1f, 100.0f);
        glm::mat4 viewMat = m_render->get_view();
        //给shader设置MVP矩阵
        m_render->set_shader("modelMat",modelMat);
        m_render->set_shader("projectMat",projectMat);
        m_render->set_shader("viewMat",viewMat);
        // draw
        m_render->draw();
        m_window->update();
    }
}

void Application::set_window(Window *win){ 
    m_window = std::unique_ptr<Window>(win);
    Log::info("set_window done!!");
}

void Application::set_render(Render *rend){
    m_render = std::unique_ptr<Render>(rend);
    Log::info("set_render done!!");
}
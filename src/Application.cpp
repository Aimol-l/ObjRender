#include "Application.h"
#include "Log.h"
Application::~Application(){
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
}

Application &Application::getApp(){
    static Application m_instance; // singleton
	return m_instance;
    // TODO: 在此处插入 return 语句
}

void Application::run(){
    glEnable(GL_DEPTH_TEST);
    while (!this->m_window->close()){
        m_render->bind(); 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        //************************Lines******************************
        // glLineWidth(1); 
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // glDrawElements(GL_TRIANGLES,m_render->get_num_faces()*3, GL_UNSIGNED_INT, 0);
        // //***********************Points*******************************
        // glPointSize(2.5); 
        // glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        // glDrawElements(GL_TRIANGLES, m_render->get_num_v(), GL_UNSIGNED_INT, 0);
        //**********************mesh*********************************
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawElements(GL_TRIANGLES, m_render->get_num_faces()*3, GL_UNSIGNED_INT, 0);
         glPointSize(2.5); 
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glDrawElements(GL_TRIANGLES, m_render->get_num_faces()*3, GL_UNSIGNED_INT, 0);
        glLineWidth(2.5); 
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, m_render->get_num_faces()*3, GL_UNSIGNED_INT, 0);
        //************************************************************
        glm::mat4 modelMat = glm::mat4(1.0f);
        glm::mat4 projectMat = glm::perspective(glm::radians(45.0f),1024.0f / 800.0f, 0.1f, 100.0f);
        glm::mat4 viewMat = m_render->get_view();
        //给shader设置MVP矩阵
        m_render->set_shader("modelMat",modelMat);
        m_render->set_shader("projectMat",projectMat);
        m_render->set_shader("viewMat",viewMat);
        m_render->unbind();
        m_window->update();
    }
    // m_window->terminate();
}

void Application::set_window(Window *win){ 
    m_window = std::unique_ptr<Window>(win);
    Log::info("set_window done!!");
}

void Application::set_render(Render *rend){
    m_render = std::unique_ptr<Render>(rend);
    Log::info("set_render done!!");
}
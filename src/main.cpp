#include <iostream>
#include <memory>
#include "Window.h"
#include "Render.h"
#include "Application.h"

int main(int argc, char const *argv[]){
    Window * win = new Window();
    Render* rend = new Render();
    //*******************************************************************************
    if(!win->create_window(1500, 1200, "Opengl 3D 模型渲染Demo", false)){
        std::cout<<"create window failed"<<std::endl;
        glfwTerminate();
        return 0;
    }
    //*******************************************************************************
    auto pos     = glm::vec3(0.0f, 0.0f, 5.0f);      //相机位置
    auto forward = glm::vec3(0.0f, 0.0f, 1.0f);   //相机方向
    auto up      = glm::vec3(0.0f, 1.0f, 0.0f);      //正上方向
    const std::string vertex_path = "../assets/shader/shader.vs";
    const std::string fragment_path ="../assets/shader/shader.fs";
    const std::string model_path = "../assets/obj/moon.obj";

    rend->add_shader(vertex_path,fragment_path);
    rend->add_model(model_path);
    rend->add_camera(pos,forward,up);
    //*******************************************************************************
    auto &app = Application::getApp();
    app.set_window(win);
    app.set_render(rend);
    app.run();
    return 0;
}


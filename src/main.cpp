#include <iostream>
#include <memory>
#include "Window.h"
#include "Render.h"
#include "Lighting.h"
#include "Application.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

int main(int argc, char const *argv[]){
    auto win = std::make_unique<ren::Window>();
    auto rend = std::make_unique<ren::Render>();
    //*******************************************************************************
    if(!win->create_window(1280, 960, "Opengl 3D 模型渲染Demo", false)){
        std::cout<<"create window failed"<<std::endl;
        glfwTerminate();
        return 0;
    }
    //*******************************************************************************
    auto pos     = glm::vec3(0.0f, 0.0f, 10.0f);      //相机位置
    auto forward = glm::vec3(0.0f, 0.0f, 1.0f);   //相机方向
    auto up      = glm::vec3(0.0f, 1.0f, 0.0f);      //正上方向
    const std::string vertex_path = "../assets/shader/shader.vs";
    const std::string fragment_path ="../assets/shader/shader.fs";
    const std::string model_path = "../assets/obj/moon.obj";

    rend->add_shader(vertex_path,fragment_path);
    rend->add_model(model_path);
    rend->add_camera(pos,forward,up);
    // 添加一个平行光
    // const std::string light_model = "../assets/obj/123456.obj";
    // auto light = std::make_unique<ren::Lighting>(1,light_model);
    // rend->add_light(light);
    //*******************************************************************************
    auto &app = ren::Application::get_app();
    app.set_window(win);
    app.set_render(rend);
    app.run();
    return 0;
}


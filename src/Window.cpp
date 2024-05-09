#include "Window.h"
#include "Log.h"
#include "globals.h"


bool ren::Window::m_pressed = false; 
glm::vec2 ren::Window::LASTPOS = {0,0};
float ren::Window::SPEED = 0.1f;
ren::Camera* ren::Window::m_camera = Camera::get_instence();

ren::Window::Window(){

}

ren::Window::~Window(){
    // 清理imgui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    glfwDestroyWindow(m_window);
    glfwTerminate();

}

bool ren::Window::close(){
    return glfwWindowShouldClose(m_window);
}
void ren::Window::update(){
    glfwPollEvents();
    this->render_imgui(); // 更新
    glfwSwapBuffers(m_window);
}

void ren::Window::init_imgui(){
    // 设置imgui上下文
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    m_io = &ImGui::GetIO(); (void)m_io;
    m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // 设置主题颜色风格
    // ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}
void ren::Window::render_imgui(){
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize({m_size[0] / 4, m_size[1]}); 
    //*******************************************要的渲染各种组件****************************************
    static float f = 0.0f;
    static int counter = 0;
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &show_another_window);
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / m_io->Framerate, m_io->Framerate);
    ImGui::End();
    //*************************************************************************************
    ImGui::End();
    //***********************************************************************************
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}   

bool ren::Window::create_window(uint w, uint h, const char *title, bool is_full){
    // 初始化GLFW
    if (!glfwInit()) {
        const char *errmsg = nullptr;
        glfwGetError(&errmsg);
        if (!errmsg) errmsg = "(no error)";
        std::string error = "failed to initialize GLFW: " + *errmsg;
        Log::error(error);
        // std::cerr << "failed to initialize GLFW: " << errmsg << '\n';
        return false;
    }
    m_size.at(0) = w;
    m_size.at(1) = h;
    // 配置GLFW 4.6版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //opengl的大版本是4 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); //opengl的小版本是6
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //选择核心模式，而不是兼容模式
    if (is_full){
        m_window = glfwCreateWindow(m_size.at(0), m_size.at(1), title, glfwGetPrimaryMonitor(), nullptr);
    }else{
        m_window = glfwCreateWindow(m_size.at(0), m_size.at(1), title, nullptr, nullptr);
    }
    if (!m_window) {
        glfwTerminate();
        Log::error("Create window failed!");
        return false;
    }
    glfwMakeContextCurrent(m_window);
    // glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // 设置回调函数
    glfwSetKeyCallback(m_window,this->key_callback);
    glfwSetCursorPosCallback(m_window, this->mouse_moveBack);
    glfwSetMouseButtonCallback(m_window, this->mouse_clickBack);
    glfwSetScrollCallback(m_window, this->scroll_callback); 
    // Load glXXX function pointers (only after this you may use OpenGL functions)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        // std::cerr << "GLAD failed to load GL functions\n";
        Log::error("GLAD failed to load GL functions!!");
        return false;
    }
    std::string version = (const char *)glGetString(GL_VERSION);
    Log::info( "OpenGL version: " + version);

    glfwSetWindowAttrib(m_window, GLFW_RESIZABLE, GLFW_FALSE);//控制是否缩放
	glViewport(0, 0, static_cast<GLsizei>(m_size.at(0)), static_cast<GLsizei>(m_size.at(1)));
    //************************
    this->init_imgui();
    return true;
}


void ren::Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    // 处理WASD键盘输入
    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        // 处理按下或重复W键的情况
        m_camera->translate(0,0,SPEED);
        std::cout << "W key pressed or repeated" << std::endl;
    }
    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        // 处理按下或重复W键的情况
        m_camera->translate(-SPEED,0,0);
        std::cout << "A key pressed or repeated" << std::endl;
    }
    if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        // 处理按下或重复W键的情况
        m_camera->translate(0,0,-SPEED);
        std::cout << "S key pressed or repeated" << std::endl;
    }
    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        // 处理按下或重复D键的情况
        m_camera->translate(SPEED,0,0);
        std::cout << "D key pressed or repeated" << std::endl;
    }
    if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        // 处理按下或重复W键的情况
        m_camera->translate(0,SPEED,0);
        std::cout << "up key pressed or repeated" << std::endl;
    }
    if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        // 处理按下或重复W键的情况
        m_camera->translate(0,-SPEED,0);
        std::cout << "Down key pressed or repeated" << std::endl;
    }
}

void ren::Window::mouse_moveBack(GLFWwindow *window, double xpos, double ypos){
    if(m_pressed){
        glm::vec2 dPos = glm::vec2{xpos,ypos} - LASTPOS;
        LASTPOS = glm::vec2{xpos,ypos};
        m_camera->rotate(dPos.y*0.2f,dPos.x*0.2f,0);
    }
}
void ren::Window::mouse_clickBack(GLFWwindow *window, int button, int action, int mods){
    Log::info("mouse_clickBack");
    // 鼠标点击处理逻辑
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) { //左键按压
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        LASTPOS = glm::vec2{xpos,ypos}; 
        m_pressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) { //左键释放
       m_pressed = false;
    }
}
void ren::Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    std::cout<<std::format(" {} ,{}",xoffset,yoffset)<<std::endl;
    // glob_model_scale +=  glm::vec3{yoffset * 0.05,yoffset * 0.05,yoffset * 0.05};
    m_camera->translate(0,0,yoffset * 0.5f);
}
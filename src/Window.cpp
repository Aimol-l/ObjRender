#include "Window.h"
#include "Log.h"

Window::Window(){
   
}
Window::~Window(){
    if(m_window) glfwTerminate();
}
int Window::close(){
    if(m_window) return glfwWindowShouldClose(m_window);
    return false;
}
void Window::update() const{
    if(m_window) glfwSwapBuffers(m_window);
    glfwPollEvents();
}
bool Window::create_window(uint w, uint h, const char *title, bool is_full){
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
    glfwSetKeyCallback(m_window,key_callback);
    glfwSetCursorPosCallback(m_window, mouse_moveBack);
    glfwSetMouseButtonCallback(m_window, mouse_clickBack);
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
    return true;
}


#include "Event.h"
#include "Log.h"



static bool PRESSED = false; 
static glm::vec2 LASTPOS = {0,0};
static float SPEED = 0.1f;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
    // float currentFrame = glfwGetTime();
    // deltaTime = currentFrame - lastFrame;
    // lastFrame = currentFrame;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    // 处理WASD键盘输入
    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        // 处理按下或重复W键的情况
        CAMERA->translate(0,0,SPEED);
        std::cout << "W key pressed or repeated" << std::endl;
    }
    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        // 处理按下或重复W键的情况
        CAMERA->translate(-SPEED,0,0);
        std::cout << "A key pressed or repeated" << std::endl;
    }
    if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        // 处理按下或重复W键的情况
        CAMERA->translate(0,0,-SPEED);
        std::cout << "S key pressed or repeated" << std::endl;
    }
    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        // 处理按下或重复D键的情况
        CAMERA->translate(SPEED,0,0);
        std::cout << "D key pressed or repeated" << std::endl;
    }
    if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        // 处理按下或重复W键的情况
        CAMERA->translate(0,SPEED,0);
        std::cout << "up key pressed or repeated" << std::endl;
    }
    if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        // 处理按下或重复W键的情况
        CAMERA->translate(0,-SPEED,0);
        std::cout << "Down key pressed or repeated" << std::endl;
    }
}

void mouse_moveBack(GLFWwindow *window, double xpos, double ypos){
    if(PRESSED){
        glm::vec2 dPos = glm::vec2{xpos,ypos} - LASTPOS;
        LASTPOS = glm::vec2{xpos,ypos};
        CAMERA->rotate(dPos.y*0.2f,dPos.x*0.2f,0);
    }
}
void mouse_clickBack(GLFWwindow *window, int button, int action, int mods){
    Log::info("mouse_clickBack");
    // 鼠标点击处理逻辑
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) { //左键按压
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        LASTPOS = glm::vec2{xpos,ypos}; 
        PRESSED = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) { //左键释放
       PRESSED = false;
    }
}

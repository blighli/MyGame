//
// Created by liqilei on 2019-11-28.
//

#include "WindowManager.h"

#include <iostream>
#include <sstream>

using namespace std;

void showFPS(GLFWwindow* window);
void error_callback(int error, const char* description);
void window_close_callback(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void size_callback(GLFWwindow* window, int width, int height);
void drop_callback(GLFWwindow* window, int count, const char** paths);
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

WindowManager::WindowManager(bool fullScreen, int width, int height, const char* title) {
    this->fullScreen = fullScreen;
    this->width = width;
    this->height = height;
    this->title = title;
    window = NULL;
    wireFrame = false;

    rot = 0;
    distance = 1.0;
}

int WindowManager::init() {
    //初始化glfw
    if (!glfwInit())
    {
        std::cerr<<"GLFW initialization failed!"<<std::endl;
        return -1;
    }

    //设置各种回调函数
    glfwSetErrorCallback(error_callback);

    //设置OpenGL版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //创建窗口
    if(fullScreen)
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        if(mode)
        {
            window = glfwCreateWindow(mode->width, mode->height, title, monitor, NULL);
        }
    }
    else
    {
        window = glfwCreateWindow(width, height, title, NULL, NULL);
    }
    if (!window)
    {
        std::cerr<<"GLFW create window failed!"<< std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowUserPointer(window, (void*)this);

    //创建Context
    glfwMakeContextCurrent(window);

    //键盘按键
    glfwSetKeyCallback(window, key_callback);
    //鼠标按键
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    //鼠标移动
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    //窗口大小改变
    glfwSetFramebufferSizeCallback(window, size_callback);
    //文件拖拽到窗口
    glfwSetDropCallback(window, drop_callback);
    //窗口关闭
    glfwSetWindowCloseCallback(window, window_close_callback);
}

int WindowManager::getWidth() {
    return this->width;
}

int WindowManager::getHeight() {
    return this->height;
}

GLFWwindow *WindowManager::getWindow() const {
    return window;
}

WindowManager::~WindowManager() {
    //清理glfw资源
    glfwDestroyWindow(window);
    glfwTerminate();
}

const char *WindowManager::getTitle() const {
    return title;
}

float WindowManager::getRot() const {
    return rot;
}

void WindowManager::setRot(float rot) {
    WindowManager::rot = rot;
}

float WindowManager::getDistance() const {
    return distance;
}

void WindowManager::setDistance(float distance) {
    WindowManager::distance = distance;
}

int WindowManager::getLastXpos() const {
    return lastXpos;
}

void WindowManager::setLastXpos(int lastXpos) {
    WindowManager::lastXpos = lastXpos;
}

int WindowManager::getLastYpos() const {
    return lastYpos;
}

void WindowManager::setLastYpos(int lastYpos) {
    WindowManager::lastYpos = lastYpos;
}

void showFPS(GLFWwindow* window)
{
    static double previousSeconds = 0.0;
    static int frameCount = 0;
    double elapsedSeconds = 0;
    double currentSeconds = glfwGetTime();

    elapsedSeconds = currentSeconds - previousSeconds;

    //每秒最多更新4次
    if(elapsedSeconds > 0.25)
    {
        previousSeconds = currentSeconds;
        double fps = (double)frameCount / elapsedSeconds;
        double msPerFrame = 1000.0 / fps;

        std::ostringstream outs;
        outs.precision(3);
        outs << std::fixed
             << "Main Window" << "    "
             << "FPS:" << fps << "    "
             << "Frame Time:" << msPerFrame << " (ms)";
        glfwSetWindowTitle(window, outs.str().c_str());

        frameCount = 0;
    }

    frameCount++;
}

void error_callback(int error, const char* description)
{
    cout<<"Error:"<<description<<endl;
}

void window_close_callback(GLFWwindow* window){
    cout<<"Status:Close window"<<endl;
    //glfwSetWindowShouldClose(window, GLFW_FALSE);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    static bool wireFrame = false;
    cout<<"Status: Key Pressed = "<<key<<endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key == GLFW_KEY_W && action == GLFW_PRESS){

        wireFrame = !wireFrame;
        if(wireFrame){

            glEnable( GL_POLYGON_OFFSET_FILL );
            glPolygonOffset(0.1,0.2);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else{
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }
}

void size_callback(GLFWwindow* window, int width, int height){
    cout<<"Status: Window width="<<width<<",height="<<height<<endl;
    glViewport(0, 0, width, height);
}

void drop_callback(GLFWwindow* window, int count, const char** paths)
{
    for (int i = 0;  i < count;  i++) {
        cout<<"Status: Filename = "<<paths[i]<<endl;
    }
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{

    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS)
    {
        WindowManager* wm = (WindowManager*)glfwGetWindowUserPointer(window);
        double dX = xpos - wm->getLastXpos();
        double dY = ypos - wm->getLastYpos();
        wm->setLastXpos(xpos);
        wm->setLastYpos(ypos);

        int width = 0;
        int height = 0;
        glfwGetWindowSize(window, &width, &height);

        float rot = wm->getRot();
        rot += dX / (float)width * 180.0;
        if(rot > 360)
            rot -= 360;
        if(rot < 0)
            rot +=360;
        wm->setRot(rot);
        cout<<"Status: Mouse Move rot="<< rot <<endl;
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        WindowManager* wm = (WindowManager*)glfwGetWindowUserPointer(window);
        double xpos = 0, ypos = 0;
        glfwGetCursorPos(window, &xpos, &ypos);
        wm->setLastXpos(xpos);
        wm->setLastYpos(ypos);
    }
}



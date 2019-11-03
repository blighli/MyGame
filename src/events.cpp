//
// Created by liqilei on 2018/12/27.
//
#include <sstream>
#include "events.h"

using namespace std;

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
    cout<<"Status: Key Pressed = "<<key<<endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void size_callback(GLFWwindow* window, int width, int height){
    cout<<"Status: Window width="<<width<<",height="<<height<<endl;
}

void drop_callback(GLFWwindow* window, int count, const char** paths)
{
    for (int i = 0;  i < count;  i++) {
        cout<<"Status: Filename = "<<paths[i]<<endl;
    }
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    cout<<"Status: Mouse Move X="<<xpos<<",Y="<<ypos<<endl;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        cout<<"Status: Mouse Pressed X="<<xpos<<",Y="<<ypos<<endl;
    }
}
//
// Created by liqilei on 2018/12/27.
//

#include "events.h"

using namespace std;

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
    cout<<"Status: Key Pressed: "<<key<<endl;
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
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <iostream>

#include "render.h"

using namespace std;

void Render()
{
    double time = glfwGetTime();
    cout<<"Status: Reander Time: "<<time<<endl;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    {
        glColor3f(1.0f,0.0f,0.0f);
        glVertex2f(0.0f, 0.5f);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex2f(-0.5f,-0.5f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.5f, -0.5f);
    }
    glEnd();
}

void error_callback(int error, const char* description)
{
    cout<<"Error: "<<description<<endl;
}

void window_close_callback(GLFWwindow* window){
    cout<<"Status: Close window: "<<"Main Window"<<endl;
    //glfwSetWindowShouldClose(window, GLFW_FALSE);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    cout<<"Status: Key Pressed: "<<key<<endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
    cout<<"Status: Window width="<<width<<",height="<<height<<endl;
}

void drop_callback(GLFWwindow* window, int count, const char** paths)
{
    int i;
    for (i = 0;  i < count;  i++)
        cout<<"Status: Filename = "<<paths[i]<<endl;
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
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


int main()
{
    //初始化glfw
    if (!glfwInit())
    {
        cout<<"glfwInit failed!"<<endl;
        return -1;
    }

    //设置OpenGL版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    //创建窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "Main Window", nullptr, nullptr);
    if (!window)
    {
        cout<<"glfwCreateWindow failed!"<<endl;
        glfwTerminate();
        return -1;
    }

    //创建Context
    glfwMakeContextCurrent(window);

    //只能创建Context后才能初始化glew
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        cout<<"Error: "<<glewGetErrorString(err)<<endl;
        return -1;
    }
    else{
        cout<<"Status: Using GLEW"<<glewGetString(GLEW_VERSION)<<endl;
    }
    //设置各种回调函数
    glfwSetErrorCallback(error_callback);
    glfwSetWindowCloseCallback(window, window_close_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, size_callback);
    glfwSetDropCallback(window, drop_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSwapInterval(1);

    setup();

    //处理事件
    while (!glfwWindowShouldClose(window))
    {
        //Render();
        render(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
        //glfwWaitEvents();
    }

    //清理glfw资源
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
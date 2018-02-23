#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <iostream>

using namespace std;

void Render()
{
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

int main()
{
    //初始化glfw
    if (!glfwInit())
    {
        cout<<"glfwInit failed!"<<endl;
        return -1;
    }

    //设置错误处理函数
    glfwSetErrorCallback(error_callback);

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

    //处理事件
    while (!glfwWindowShouldClose(window))
    {
        Render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //清理glfw资源
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
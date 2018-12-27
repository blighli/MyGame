#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <iostream>

#include "render.h"
#include "events.h"

using namespace std;

int main()
{
    //初始化glfw
    if (!glfwInit())
    {
        cout<<"glfwInit failed!"<<endl;
        return -1;
    }

    //设置各种回调函数
    glfwSetErrorCallback(error_callback);

    //设置OpenGL版本
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


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

    glfwSetWindowCloseCallback(window, window_close_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, size_callback);
    glfwSetDropCallback(window, drop_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSwapInterval(1);

    //setup();

    //处理事件
    while (!glfwWindowShouldClose(window))
    {
        //render(window);
        glfwSwapBuffers(window);
        //glfwPollEvents();
        glfwWaitEvents();
    }

    //清理glfw资源
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

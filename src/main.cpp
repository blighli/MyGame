#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "events.h"

int main()
{
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
    GLFWwindow* window = glfwCreateWindow(800, 600, "Main Window", nullptr, nullptr);
    if (!window)
    {
        std::cerr<<"GLFW create window failed!"<< std::endl;
        glfwTerminate();
        return -1;
    }

    //创建Context
    glfwMakeContextCurrent(window);

    //只能创建Context后才能初始化glew
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cout<<"Error: "<<glewGetErrorString(err)<< std::endl;
        return -1;
    }
    else{
        std::cout<<"Status: Using GLEW"<<glewGetString(GLEW_VERSION)<<std::endl;
    }

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

    //glfwSwapInterval(1);

    //处理事件
    while (!glfwWindowShouldClose(window))
    {
        showFPS(window);

        glfwPollEvents();

        glClearColor(0.23f, 0.38f, 0.47f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    //清理glfw资源
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

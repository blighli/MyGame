#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "events.h"

const char* WINDOW_TITLE = "Main Window";
bool gFullScreen = false;

static const GLchar* ReadShader(const char* filename){
    FILE* file =  fopen(filename, "rb");
    if (!file)
    {
        std::cerr<<"ReadShader failed!"<<std::endl;
        return NULL;
    }
    fseek( file, 0, SEEK_END );
    int len = ftell( file );
    fseek( file, 0, SEEK_SET );

    GLchar* source = new GLchar[len+1];
    fread( source, 1, len, file );
    fclose( file );

    source[len] = 0;

    return const_cast<const GLchar*>(source);
}

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
    GLFWwindow *window = NULL;
    if(gFullScreen)
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        if(mode)
        {
            window = glfwCreateWindow(mode->width, mode->height, WINDOW_TITLE, monitor, NULL);
        }
    }
    else
    {
        window = glfwCreateWindow(800, 600, WINDOW_TITLE, NULL, NULL);
    }
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

    GLfloat vertices[] = {
            0.0f, 0.5f, 0.f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
    };

    const GLchar* vShaderSource = ReadShader("media/shader/vertex.shader");
    const GLchar* fShaderSource = ReadShader("media/shader/fragment.shader");

    GLuint program = glCreateProgram();
    GLuint shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource( shader, 1, &vShaderSource, NULL );
    glCompileShader( shader );
    glAttachShader( program, shader );

    shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource( shader, 1, &fShaderSource, NULL );
    glCompileShader( shader );
    glAttachShader( program, shader );

    glLinkProgram( program );
    glUseProgram( program);

    GLuint vbo;
    GLuint vao;

    glCreateBuffers(1, &vbo);
    glNamedBufferStorage(vbo, sizeof(vertices), vertices, 0);

    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);


    //处理事件
    while (!glfwWindowShouldClose(window))
    {
        showFPS(window);

        glfwPollEvents();

        static const float bgColor[] = {0.23f, 0.38f, 0.47f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, bgColor);

        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    //清理glfw资源
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

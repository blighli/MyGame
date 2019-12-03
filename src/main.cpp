#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "WindowManager.h"
#include "ShaderProgram.h"

int main()
{
    WindowManager windowManager(false, 800,600, "Main Window");
    windowManager.init();

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

    GLfloat vertices[] = {
            0.0f, 0.5f, 0.f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    ShaderProgram program;
    program.loadShader(GL_VERTEX_SHADER, "media/shader/vertex.shader");
    program.loadShader(GL_FRAGMENT_SHADER, "media/shader/fragment.shader");
    program.use();

    GLuint vbo;
    GLuint vao;

    //glCreateBuffers(1, &vbo);
    //glNamedBufferStorage(vbo, sizeof(vertices), vertices, 0);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glCreateVertexArrays(1, &vao);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);



    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, NULL);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (GLvoid*)(sizeof(GLfloat) * 3));
    glEnableVertexAttribArray(1);


    //处理事件
    while (!glfwWindowShouldClose(windowManager.getWindow()))
    {
        glfwPollEvents();

        static const float bgColor[] = {0.23f, 0.38f, 0.47f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, bgColor);

        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        glfwSwapBuffers(windowManager.getWindow());
    }

    return 0;
}

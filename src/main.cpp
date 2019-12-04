#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "WindowManager.h"
#include "ShaderProgram.h"
#include "ModelObject.h"

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

    ModelObject object;
    object.loadObject("media/object/triangle.txt");
    //object.createSphere();

    ShaderProgram program;
    program.loadShader(GL_VERTEX_SHADER, "media/shader/vertex.shader");
    program.loadShader(GL_FRAGMENT_SHADER, "media/shader/fragment.shader");
    program.use();

    GLuint vbo;
    //glCreateBuffers(1, &vbo);
    //glNamedBufferStorage(vbo, sizeof(vertices), vertices, 0);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * object.getVertexCount() * 6, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * object.getVertexCount() * 3, object.getVertices());
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * object.getVertexCount() * 3, sizeof(GLfloat) * object.getVertexCount() * 3, object.getColors());

    GLuint vao;
    //glCreateVertexArrays(1, &vao);
    glGenVertexArrays(1, &vao);
    object.setObjectId(vao);

    glBindVertexArray(object.getObjectId());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(GLfloat) * object.getVertexCount() * 3));
    glEnableVertexAttribArray(1);


    //处理事件
    while (!glfwWindowShouldClose(windowManager.getWindow()))
    {
        glfwPollEvents();

        static const float bgColor[] = {0.23f, 0.38f, 0.47f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, bgColor);

        glBindVertexArray(object.getObjectId());

        glDrawArrays(GL_TRIANGLE_STRIP, 0, object.getVertexCount());

        glBindVertexArray(0);

        glfwSwapBuffers(windowManager.getWindow());
    }

    return 0;
}

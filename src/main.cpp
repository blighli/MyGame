#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "WindowManager.h"
#include "ShaderProgram.h"
#include "ModelObject.h"

void prepare(ModelObject& object){
    GLuint vao;
    //glCreateVertexArrays(1, &vao);
    glGenVertexArrays(1, &vao);
    object.setObjectId(vao);
    glBindVertexArray(object.getObjectId());

    GLuint vbo;
    //glCreateBuffers(1, &vbo);
    //glNamedBufferStorage(vbo, sizeof(vertices), vertices, 0);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    int vertexBufferSize = sizeof(GLfloat) * object.getVertexCount() * 3;
    int colorBufferSize = 0;
    if(object.getColors() != NULL){
        colorBufferSize = sizeof(GLfloat) * object.getVertexCount() * 3;
    }
    int bufferSize = vertexBufferSize + colorBufferSize;

    glBufferData(GL_ARRAY_BUFFER, bufferSize, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertexBufferSize, object.getVertices());
    glBufferSubData(GL_ARRAY_BUFFER, vertexBufferSize, colorBufferSize, object.getColors());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *) (0));
    glEnableVertexAttribArray(0);

    if(object.getColors() != NULL) {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *) (vertexBufferSize));
        glEnableVertexAttribArray(1);
    }
}

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
    prepare(object);

    ModelObject mat;
    mat.createMat();
    prepare(mat);

    ShaderProgram program;
    program.loadShader(GL_VERTEX_SHADER, "media/shader/vertex.shader");
    program.loadShader(GL_FRAGMENT_SHADER, "media/shader/fragment.shader");
    program.use();

    glEnable(GL_DEPTH_TEST);
    //处理事件
    while (!glfwWindowShouldClose(windowManager.getWindow()))
    {
        glfwPollEvents();

        static const float bgColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, bgColor);
        static const float depth = 1.0;
        glClearBufferfv(GL_DEPTH, 0, &depth);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glBindVertexArray(object.getObjectId());
        glDrawArrays(GL_TRIANGLE_STRIP, 0, object.getVertexCount());

        glBindVertexArray(mat.getObjectId());
        glDrawArrays(GL_LINE_STRIP, 0, mat.getVertexCount());

        glBindVertexArray(0);

        glfwSwapBuffers(windowManager.getWindow());
    }

    return 0;
}

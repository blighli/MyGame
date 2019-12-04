#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "WindowManager.h"
#include "ShaderProgram.h"
#include "ModelObject.h"

void bindObject(ModelObject& object){

    GLuint vao;
    glGenVertexArrays(1, &vao);
    object.setObjectId(vao);
    glBindVertexArray(object.getObjectId());

    if(object.getVertices() != NULL) {
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        int vertexBufferSize = sizeof(GLfloat) * object.getVertexCount() * 3;
        glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, object.getVertices(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *) (0));
        glEnableVertexAttribArray(0);
    }
    if(object.getColors() != NULL){
        GLuint cbo;
        glGenBuffers(1, &cbo);
        glBindBuffer(GL_ARRAY_BUFFER, cbo);
        int colorBufferSize = sizeof(GLfloat) * object.getVertexCount() * 3;
        glBufferData(GL_ARRAY_BUFFER, colorBufferSize, object.getColors(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *) (0));
        glEnableVertexAttribArray(1);
    }
    if(object.getIndices() != NULL){
        GLuint ibo;
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        int indexBufferSize = sizeof(int) * object.getIndexCount();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, object.getIndices(), GL_STATIC_DRAW);
    }
}

void drawObject(ModelObject& object) {
    glBindVertexArray(object.getObjectId());
    if(object.getIndices() == NULL){
        glDrawArrays(GL_TRIANGLES, 0, object.getVertexCount());
    }
    else{
        glDrawElements(GL_TRIANGLES, object.getIndexCount(), GL_UNSIGNED_INT,  0);
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
    bindObject(object);

    ModelObject mat;
    mat.createMat();
    bindObject(mat);

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

        drawObject(object);
        drawObject(mat);

        glfwSwapBuffers(windowManager.getWindow());
    }

    return 0;
}

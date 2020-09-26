#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "WindowManager.h"
#include "ShaderProgram.h"
#include "ModelObject.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <FreeImage/FreeImage.h>

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

    const char* filename="media/image/demo.jpg";
    FreeImage_Initialise();
    //image format
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    //pointer to the image, once loaded
    FIBITMAP *dib(0);
    //pointer to the image data
    BYTE* bits(0);
    //image width and height
    unsigned int width(0), height(0);
    //OpenGL's image ID to map to
    GLuint gl_texID;

    //check the file signature and deduce its format
    fif = FreeImage_GetFileType(filename, 0);
    //if still unknown, try to guess the file format from the file extension
    if(fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(filename);
    //if still unkown, return failure
    if(fif == FIF_UNKNOWN)
        return false;

    //check that the plugin has reading capabilities and load the file
    if(FreeImage_FIFSupportsReading(fif))
        dib = FreeImage_Load(fif, filename);
    //if the image failed to load, return failure
    if(!dib)
        return false;

    //retrieve the image data
    bits = FreeImage_GetBits(dib);
    //get the image width and height
    width = FreeImage_GetWidth(dib);
    height = FreeImage_GetHeight(dib);
    std::cout<<"w="<<width<<"h="<<height<<std::endl;


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

        float rot = windowManager.getRot();
        //std::cout<<"rot = "<<rot<<std::endl;

        glm::mat4 Proj = glm::perspective(glm::radians(45.0f), 4.0f/3.0f, 0.1f, 10.0f);
        glm::mat4 View = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 Model = glm::rotate(glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 MPV = Proj * View * Model;

        GLint loc = glGetUniformLocation(program.getProgram(), "mvp");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(MPV));

        drawObject(object);
        drawObject(mat);

        glfwSwapBuffers(windowManager.getWindow());
    }

    return 0;
}

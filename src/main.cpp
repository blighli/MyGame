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

int main()
{
    if (!glfwInit())
    {
        cout<<"glfwInit failed!"<<endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Main Window", nullptr, nullptr);
    if (!window)
    {
        cout<<"glfwCreateWindow failed!"<<endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        cout<<"Error: "<<glewGetErrorString(err)<<endl;
    }
    else{
        cout<<"Status: Using GLEW"<<glewGetString(GLEW_VERSION)<<endl;
    }

    while (!glfwWindowShouldClose(window))
    {
        Render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
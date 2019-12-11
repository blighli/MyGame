//
// Created by liqilei on 2019-11-28.
//

#ifndef MYGAME_WINDOWMANAGER_H
#define MYGAME_WINDOWMANAGER_H

#include <GLFW/glfw3.h>

class WindowManager {
public:
    WindowManager(bool fullScreen, int width, int height, const char* title);
    int init();
    int getWidth();
    int getHeight();
private:
    GLFWwindow *window;
public:
    GLFWwindow *getWindow() const;
    virtual ~WindowManager();
    const char *getTitle() const;

private:
    bool fullScreen;
    bool wireFrame;
    int width;
    int height;
    const char* title;

    int lastXpos;
    int lastYpos;
    float rot;
    float distance;
public:
    int getLastXpos() const;
    void setLastXpos(int lastXpos);

    int getLastYpos() const;
    void setLastYpos(int lastYpos);

    float getRot() const;
    void setRot(float rot);

    float getDistance() const;
    void setDistance(float distance);
};


#endif //MYGAME_WINDOWMANAGER_H

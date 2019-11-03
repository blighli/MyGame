//
// Created by liqilei on 2018/12/27.
//

#ifndef PROJECT_EVENTS_H
#define PROJECT_EVENTS_H

#include <iostream>
#include <GLFW/glfw3.h>

void showFPS(GLFWwindow* window);

void error_callback(int error, const char* description);
void window_close_callback(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void size_callback(GLFWwindow* window, int width, int height);
void drop_callback(GLFWwindow* window, int count, const char** paths);
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


#endif //PROJECT_EVENTS_H

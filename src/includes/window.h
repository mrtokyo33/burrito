#ifndef WINDOW_H
#define WINDOW_H

#include "config.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLFWwindow* initWindow(int width, int height, const char* title);
void processInput(GLFWwindow *window);
static inline void setClearColor(Color c)
{
    glClearColor(c.r, c.g, c.b, c.a);
}

#endif
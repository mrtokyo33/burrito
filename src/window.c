#include "window.h"
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    (void)window;
    glViewport(0, 0, width, height);
}

GLFWwindow* initWindow(int width, int height, const char* title)
{
    if (!glfwInit())
    {
        printf("Failed to initialize GLFW\n");
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create the window\n");
        glfwTerminate();
        return NULL;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        printf("Failed to initialize GLEW\n");
        return NULL;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    printf("OpenGL version: %s\n", glGetString(GL_VERSION));
    return window;
}

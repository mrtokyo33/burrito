#include "utils.h"
#include <GLFW/glfw3.h>

double getDeltaTime()
{
    static double last = 0.0;
    double now = glfwGetTime();

    double dt = now - last;
    last = now;

    return dt;
}
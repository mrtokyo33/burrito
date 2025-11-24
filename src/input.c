#include "input.h"
#include <string.h>

static struct {
    bool down[MAX_KEYS];
    bool pressed[MAX_KEYS];
    bool released[MAX_KEYS];
} keyboardState;

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    (void)window;
    (void)scancode;
    (void)mods;

    if (key < 0 || key >= MAX_KEYS)
        return;

    if (action == GLFW_PRESS)
    {
        keyboardState.down[key] = true;
        keyboardState.pressed[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        keyboardState.down[key] = false;
        keyboardState.released[key] = true;
    }
}

void inputInit(GLFWwindow* window)
{
    memset(&keyboardState, 0, sizeof(keyboardState));
    glfwSetKeyCallback(window, keyCallback);
}

void inputUpdate()
{
    memset(keyboardState.pressed, 0, sizeof(keyboardState.pressed));
    memset(keyboardState.released, 0, sizeof(keyboardState.released));
}

bool keyDown(int key)
{
    return keyboardState.down[key];
}

bool keyPressed(int key)
{
    return keyboardState.pressed[key];
}

bool keyReleased(int key)
{
    return keyboardState.released[key];
}
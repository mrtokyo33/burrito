#ifndef INPUT_H
#define INPUT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdbool.h>

#define MAX_KEYS 512

void inputInit(GLFWwindow* window);
void inputUpdate();

bool keyDown(int key);
bool keyPressed(int key);
bool keyReleased(int key);

#endif
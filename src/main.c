#include "config.h"
#include "input.h"
#include "window.h"
#include "image.h"
#include "renderer.h"
#include "burrito.h"
#include "utils.h"
#include "cannon.h"

#include <stddef.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

void clear_screen();

int main(void)
{
    GLFWwindow* window = initWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    if (window == NULL)
        return -1;

    inputInit(window);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    initRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);

    Texture ground = loadTexture("src/assets/images/ground.png");
    Texture background = loadTexture("src/assets/images/background.png");

    Texture baseCannonText = loadTexture("src/assets/images/baseCannon.png");
    Texture cannonText = loadTexture("src/assets/images/cannon.png");
    Cannon cannon = initCannon(0, baseCannonText, cannonText);

    Texture burritoText = loadTexture("src/assets/images/burrito.png");

    while (!glfwWindowShouldClose(window))
    {
        double dt = getDeltaTime();

        inputUpdate();
        glfwPollEvents();
        if (keyPressed(GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, 1);
        
        updateCannon(&cannon, &dt);

        clear_screen();
        drawTexture(background, 0, 0);
        drawTexture(ground, 0, 0);
        
        drawCannon(&cannon);

        glfwSwapBuffers(window);
    }

    freeTexture(&background);
    freeTexture(&ground);
    freeTexture(&cannonText);
    freeTexture(&baseCannonText);
    freeTexture(&burritoText);
    glfwTerminate();
    return 0;
}

void clear_screen()
{
    setClearColor(COLOR_BACKGROUND);
    glClear(GL_COLOR_BUFFER_BIT);
}
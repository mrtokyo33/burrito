#include "burrito.h"
#include "input.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Burrito initBurrito(float initX, float initY, float vx0, float vy0, Texture text)
{
    Burrito b;
    b.x = initX;
    b.y = initY;
    b.text = text;
    b.hspd = vx0 * UNITY;
    b.vspd = -vy0 * UNITY;

    return b;
}

void drawBurrito(Burrito *b)
{
    drawTexture(b->text, b->x, b->y);
}

void moveBurrito(Burrito *b, float *dt)
{
    b->vspd += GRAVITY * (*dt);

    b->x += b->hspd * (*dt);
    b->y += b->vspd * (*dt);
}

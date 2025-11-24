#ifndef BURRITO_H
#define BURRITO_H

#include "renderer.h"
#include "config.h"

typedef struct
{
    Texture text;
    float x, y;
    float hspd, vspd;
    float mass;
} Burrito;

Burrito initBurrito(float initX, float initY, float vx0, float vy0, Texture text);
void drawBurrito(Burrito *b);
void moveBurrito(Burrito *b, float *dt);

#endif
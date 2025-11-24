#ifndef CANNON_H
#define CANNON_H

#include "renderer.h"

typedef struct {
    float angle;
    double timer;
    Texture baseCannonText;
    Texture cannonText;
} Cannon;

Cannon initCannon(float angle, Texture baseCannonText, Texture cannonText);

void updateCannon(Cannon *c, double *dt);

void drawCannon(Cannon *c);

#endif
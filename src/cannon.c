#include "cannon.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14
#endif

static const float BASE_CANNON_X = 100.0f;
static const float BASE_CANNON_Y = 650.0f;
static const float CANNON_X = 120.0f;
static const float CANNON_Y = 648.0f;

static const int PIVOT_X_OFFSET = 15; 
static const int PIVOT_Y_OFFSET = 45;

static const float MAX_ANGLE_RAD = 85.0f * (M_PI / 180.0f);
static const float MIN_ANGLE_RAD = 0.0f;
static const float CYCLE_TIME = 2.5f;

Cannon initCannon(float angle, Texture baseCannonText, Texture cannonText)
{
    Cannon c;
    c.angle = angle;
    c.timer = 0.0;
    c.baseCannonText = baseCannonText;
    c.cannonText = cannonText;
    return c;
}

void updateCannon(Cannon *c, double *dt)
{
    c->timer += *dt;

    if (c->timer > CYCLE_TIME) {
        c->timer -= CYCLE_TIME;
    }

    double sineWave = sin(c->timer * (2.0 * M_PI / CYCLE_TIME));

    float t = (float)(sineWave + 1.0) / 2.0f;

    c->angle = MIN_ANGLE_RAD + (t * (MAX_ANGLE_RAD - MIN_ANGLE_RAD)) - 45;
}

void drawCannon(Cannon *c)
{
    drawTextureRotated(c->cannonText, CANNON_X, CANNON_Y, -c->angle, PIVOT_X_OFFSET, PIVOT_Y_OFFSET);

    drawTexture(c->baseCannonText, BASE_CANNON_X, BASE_CANNON_Y);
}
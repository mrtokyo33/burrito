#ifndef RENDERER_H
#define RENDERER_H

#include "image.h"

void initRenderer(int screenWidth, int screenHeight);

void drawTexture(Texture tex, float x, float y);

void drawTextureRotated(Texture tex, float x, float y, float angle, int pivotX, int pivotY);

#endif
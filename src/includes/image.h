#ifndef IMAGE_H
#define IMAGE_H

#include <GL/glew.h>

typedef struct {
    GLuint textureID;
    int width;
    int height;
} Texture;

Texture loadTexture(const char* filePath);
void freeTexture(Texture* tex);

#endif
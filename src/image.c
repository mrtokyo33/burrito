#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "image.h"
#include <stdio.h>

Texture loadTexture(const char* filePath)
{
    Texture tex;
    int channels;

    stbi_set_flip_vertically_on_load(1);

    unsigned char* data = stbi_load(filePath, &tex.width, &tex.height, &channels, 4);
    if (!data) {
        printf("Erro ao carregar imagem: %s\n", filePath);
        tex.textureID = 0;
        return tex;
    }

    glGenTextures(1, &tex.textureID);
    glBindTexture(GL_TEXTURE_2D, tex.textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.width, tex.height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return tex;
}


void freeTexture(Texture* tex)
{
    glDeleteTextures(1, &tex->textureID);
}
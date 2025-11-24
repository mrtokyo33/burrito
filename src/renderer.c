#include "renderer.h"
#include "shader.h"
#include <GL/glew.h>
#include <stdio.h>

static GLuint vao, vbo;
static GLuint shaderProgram;
static GLint locPos, locSize, locScreen, locTex, locAngle, locAnchor;

void initRenderer(int screenW, int screenH)
{
    float vertices[] = {
        0.0f, 1.0f,   0.0f, 1.0f,
        1.0f, 1.0f,   1.0f, 1.0f,
        1.0f, 0.0f,   1.0f, 0.0f,
        0.0f, 0.0f,   0.0f, 0.0f
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    const char* vertexSrc =
    "#version 330 core\n"
    "layout(location = 0) in vec2 aPos;\n"
    "layout(location = 1) in vec2 aUV;\n"
    "uniform vec2 uPos;\n"
    "uniform vec2 uSize;\n"
    "uniform vec2 uScreen;\n"
    "uniform float uAngle;\n"
    "uniform vec2 uAnchor;\n"
    "out vec2 vUV;\n"
    "void main()\n"
    "{\n"
    "    vec2 localPos = (aPos - uAnchor) * uSize;\n"
    "    float s = sin(uAngle);\n"
    "    float c = cos(uAngle);\n"
    "    mat2 rot = mat2(c, -s, s, c);\n"
    "    localPos = rot * localPos;\n"
    "    vec2 finalPos = localPos + uPos;\n"
    "    float x = finalPos.x / uScreen.x * 2.0 - 1.0;\n"
    "    float y = finalPos.y / uScreen.y * 2.0 - 1.0;\n"
    "    y = -y;\n"
    "    gl_Position = vec4(x, y, 0.0, 1.0);\n"
    "    vUV = vec2(aUV.x, 1.0 - aUV.y);\n"
    "}\n";

    const char* fragmentSrc =
    "#version 330 core\n"
    "in vec2 vUV;\n"
    "uniform sampler2D uTex;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = texture(uTex, vUV);\n"
    "}\n";

    shaderProgram = loadShaderProgram(vertexSrc, fragmentSrc);

    locPos = glGetUniformLocation(shaderProgram, "uPos");
    locSize = glGetUniformLocation(shaderProgram, "uSize");
    locScreen = glGetUniformLocation(shaderProgram, "uScreen");
    locTex = glGetUniformLocation(shaderProgram, "uTex");
    locAngle = glGetUniformLocation(shaderProgram, "uAngle");
    locAnchor = glGetUniformLocation(shaderProgram, "uAnchor");

    glUseProgram(shaderProgram);
    glUniform2f(locScreen, (float)screenW, (float)screenH);
    glUniform1i(locTex, 0);
}

void drawTexture(Texture tex, float x, float y)
{
    drawTextureRotated(tex, x, y, 0.0f, 0, 0);
}

void drawTextureRotated(Texture tex, float x, float y, float angle, int pivotX, int pivotY)
{
    glUseProgram(shaderProgram);
    glUniform2f(locPos, x, y);
    glUniform2f(locSize, (float)tex.width, (float)tex.height);
    glUniform1f(locAngle, angle);

    float ax = (float)pivotX / (float)tex.width;
    float ay = (float)pivotY / (float)tex.height;

    glUniform2f(locAnchor, ax, ay);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex.textureID);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
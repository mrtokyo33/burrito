#include "shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>

static char* readFile(const char* filepath)
{
    FILE* f = fopen(filepath, "rb");
    if (!f)
    {
        printf("Failed to open file: %s\n", filepath);
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* buffer = malloc(length + 1);
    if (!buffer)
    {
        printf("Failed to allocate memory for %s\n", filepath);
        fclose(f);
        return NULL;
    }

    fread(buffer, 1, length, f);
    buffer[length] = '\0';

    fclose(f);
    return buffer;
}

static GLuint compileShader(GLenum type, const char* src)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    int success;
    char log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, log);
        printf("Shader Compilation Error:\n%s\n", log);
    }

    return shader;
}

GLuint loadShaderProgram(const char* vertexPath, const char* fragmentPath)
{
    char* vertexSrc = readFile(vertexPath);
    char* fragmentSrc = readFile(fragmentPath);

    if (!vertexSrc || !fragmentSrc)
    {
        free(vertexSrc);
        free(fragmentSrc);
        return 0;
    }

    GLuint vs = compileShader(GL_VERTEX_SHADER, vertexSrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int success;
    char log[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, log);
        printf("Program Linking Error:\n%s\n", log);
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
    free(vertexSrc);
    free(fragmentSrc);

    return program;
}
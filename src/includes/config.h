#ifndef CONFIG_H
#define CONFIG_H

static const char WINDOW_TITLE[] = "Burrito";
static const int WINDOW_WIDTH  = 1280;
static const int WINDOW_HEIGHT = 720;
static const float GRAVITY = 100;
static const float UNITY = 15;

typedef struct {
    float r, g, b, a;
} Color;

static const Color COLOR_BACKGROUND = {0.2f, 0.9872f, 0.9812f, 1.0f};

#endif
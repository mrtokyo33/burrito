#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aUV;

uniform vec2 uPos;
uniform vec2 uSize;
uniform vec2 uScreen;
uniform float uAngle;
uniform vec2 uAnchor;

out vec2 vUV;

void main()
{
    vec2 localPos = (aPos - uAnchor) * uSize;
    
    float s = sin(uAngle);
    float c = cos(uAngle);
    mat2 rot = mat2(c, -s, s, c);
    localPos = rot * localPos;
    
    vec2 finalPos = localPos + uPos;
    
    float x = finalPos.x / uScreen.x * 2.0 - 1.0;
    float y = finalPos.y / uScreen.y * 2.0 - 1.0;
    
    y = -y;
    
    gl_Position = vec4(x, y, 0.0, 1.0);
    vUV = vec2(aUV.x, 1.0 - aUV.y);
}
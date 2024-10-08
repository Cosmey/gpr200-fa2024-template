#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float uTime;

out vec3 ourColor;

void main()
{
    vec3 pos = aPos;
    pos.y += sin(uTime * 2 + pos.y * 2);
    gl_Position = vec4(pos, 1.0);
    ourColor = aColor;
}
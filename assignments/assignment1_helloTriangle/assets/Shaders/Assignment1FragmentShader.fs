#version 330 core
out vec4 FragColor;

uniform float uTime;
in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0f) * (sin(uTime) * 0.5 + 0.5);
}
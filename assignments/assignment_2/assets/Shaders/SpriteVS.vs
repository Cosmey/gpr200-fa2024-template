#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform float uTime;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	//gl_Position.x = (gl_Position.x * cos(uTime)) + (gl_Position.y * -sin(uTime));
	//gl_Position.y = (gl_Position.x * sin(uTime)) + (gl_Position.y * cos(uTime));
	ourColor = aColor;
	TexCoord = aTexCoord;
}
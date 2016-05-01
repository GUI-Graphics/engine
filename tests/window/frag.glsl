#version 430 core

uniform vec3 diffuse;

out vec4 outColor;

void main()
{
	outColor = vec4(diffuse, 1.0);
}
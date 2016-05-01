#version 430 core

layout(location = 0) in vec3 position;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectMatrix;

void main()
{
	gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}
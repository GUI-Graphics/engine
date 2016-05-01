#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 vNormal;
out vec3 vPosition;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectMatrix;

void main()
{
	gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);
	vNormal = normal;
	vPosition = position;
}
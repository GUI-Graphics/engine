#version 430 core

layout(location = 0) in vec3 position;

void main()
{
	gl_Position = vec4(position.x, position.z, 0, 1);
}
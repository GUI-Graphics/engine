#version 430 core

in vec3 vPosition;
in vec3 vNormal;

uniform vec3 diffuse;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

out vec4 outColor;

void main()
{
	vec3 lightDir = normalize(lightPosition - vPosition);
	float dc = max(dot(lightDir, vNormal), 0.0f);

	vec3 viewDir = normalize(cameraPosition - vPosition);
	vec3 reflectDir = reflect(-lightDir, vNormal);
	float sc = pow(max(dot(viewDir, reflectDir), 0.0f), 32);

	outColor = vec4((0.2f + dc + sc)) * diffuse;
}
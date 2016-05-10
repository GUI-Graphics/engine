#pragma once

#include <glad/glad.h>

namespace engine
{
	class Texture
	{
	public:
		Texture(const char* filename, GLuint format = GL_RGB);

	public:
		GLuint texture;
	};
}
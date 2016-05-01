#pragma once

#include <glad\glad.h>

namespace engine
{
	class GLShader
	{
	public:
		GLShader(GLenum type) : shader(0), type(type)
		{ }

		void fromStr(const char* source);
		void fromFile(const char* filename);

	public:
		GLuint shader;
		GLenum type;
	};
}
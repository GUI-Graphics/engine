#pragma once

#include <map>
#include <glad\glad.h>
#include "renderer\GLShader.h"

namespace engine
{
	class GLProgram
	{
	public:
		GLProgram(GLShader vertexShader, GLShader fragmentShader) : vertexShader(vertexShader), fragmentShader(fragmentShader)
		{ }

		~GLProgram()
		{
			if (program) glDeleteProgram(program);
		}

		void compile();

	public:
		GLuint program;
		GLShader vertexShader;
		GLShader fragmentShader;
	};
}
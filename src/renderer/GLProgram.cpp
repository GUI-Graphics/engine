#include "renderer\GLProgram.h"

namespace engine
{
	void GLProgram::compile()
	{
		program = glCreateProgram();
		glAttachShader(program, vertexShader.shader);
		glAttachShader(program, fragmentShader.shader);
		glLinkProgram(program);

		GLint status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);

		if (status != GL_TRUE)
		{
			int infoLogLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

			char* infoLog = new char[infoLogLength];
			glGetProgramInfoLog(program, infoLogLength, 0, infoLog);

			printf("program link failed:\n%s\n", infoLog);
			delete[] infoLog;

			throw std::exception();
		}

		glDeleteShader(vertexShader.shader);
		glDeleteShader(fragmentShader.shader);
	}
}
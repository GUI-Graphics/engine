#include <fstream>
#include <sstream>
#include "renderer/GLShader.h"

namespace engine
{
	void GLShader::fromFile(const char* filename)
	{
		std::ifstream file(filename);

		if (file.fail())
		{
			printf("cannot load shader: %s\n", filename);
			throw std::exception();
		}

		std::stringstream stream;
		stream << file.rdbuf();
		fromStr(stream.str().c_str());
	}

	void GLShader::fromStr(const char* source)
	{
		shader = glCreateShader(type);

		glShaderSource(shader, 1, &source, 0);
		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

		if (status != GL_TRUE)
		{
			int infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			char* infoLog = new char[infoLogLength];
			glGetShaderInfoLog(shader, infoLogLength, 0, infoLog);

			printf("compile shader failed:\n%s", infoLog);
			delete[] infoLog;

			throw std::exception();
		}
	}
}
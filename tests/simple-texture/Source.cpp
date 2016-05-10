#include <engine.h>
#include <SOIL.h>

using namespace engine;

const char* vertexCode =
	"#version 430 core\n"

	"layout(location = 0) in vec2 position;\n"
	"layout(location = 1) in vec2 uv;\n"

	"out vec2 vUv;\n"

	"void main()\n"
	"{\n"
	"	vUv = vec2(uv.x, 1 - uv.y);\n"
	"	gl_Position = vec4(position, 0, 1);\n"
	"}\n";

const char* fragmentCode =
	"#version 430 core\n"

	"uniform sampler2D map;\n"

	"in vec2 vUv;\n"
	"out vec4 outColor;\n"

	"void main()\n"
	"{\n"
	"	outColor = texture(map, vUv);\n"
	"}\n";

int main()
{
	Window window;

	GLShader vertexShader(GL_VERTEX_SHADER);
	vertexShader.fromStr(vertexCode);
	GLShader fragmentShader(GL_FRAGMENT_SHADER);
	fragmentShader.fromStr(fragmentCode);
	GLProgram program(vertexShader, fragmentShader);
	program.compile();

	std::vector<float> verticesUvs = 
	{
		-1, -1,		0, 0,
		 1, -1,		1, 0,
		-1,  1,		0, 1,
		 1, -1,		1, 0,
		 1,  1,		1, 1,
		-1,  1,		0, 1,
	};

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vertexUvBuffer;
	glGenBuffers(1, &vertexUvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexUvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesUvs.size(), verticesUvs.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	int width, height;
	unsigned char* image = SOIL_load_image("../../resource/lake.jpg", &width, &height, 0, SOIL_LOAD_RGB);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);

	glUseProgram(program.program);

	while (window.active())
	{
		glDrawArrays(GL_TRIANGLES, 0, 6);
		window.refresh();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vertexUvBuffer);
	glDeleteTextures(1, &texture);

	return 0;
}
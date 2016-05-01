#include <engine.h>
using namespace engine;

int main()
{
	Window window;

	PlaneBufferGeometry plane(2, 2, 1, 1);
	glGenVertexArrays(1, &plane.vao);
	glBindVertexArray(plane.vao);
	plane.updateAttributes();
	glBindBuffer(GL_ARRAY_BUFFER, plane.getAttribute("position")->buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	MAKE_PROGRAM(program, "vert.glsl", "frag.glsl");

	glUseProgram(program.program);

	float time = 0;
	GLuint timeLocation = glGetUniformLocation(program.program, "time");

	while (window.active())
	{
		time += 0.003f;
		glUniform1f(timeLocation, time);
		glDrawElements(GL_TRIANGLES, (GLsizei)plane.indices.size(), GL_UNSIGNED_INT, 0);
		window.refresh();
	}

	return 0;
}
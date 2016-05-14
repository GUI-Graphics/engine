#include <engine.h>
using namespace engine;

const char* vert =
	"#version 430 core\n"

	"layout(location = 0) in vec3 position;\n"

	"void main()\n"
	"{\n"
	"	gl_Position = vec4(position.x, position.y, 0, 1);\n"
	"}\n";

const char* frag =
	"#version 430 core\n"

	"uniform float time;\n"
	"in vec4 gl_FragCoord;\n"
	"out vec4 outColor;\n"

	"float radius = 0.1 * 500;\n"

	"bool withinCircle(vec2 point, vec2 center)\n"
	"{\n"
	"	center *= vec2(800, 500);\n"
	"	return distance(point, center) < radius;\n"
	"}\n"

	"float metal(vec2 point, vec2 center)\n"
	"{\n"
	"	center *= vec2(800, 500);\n"
	"	float dist = length(point - center);\n"
	"	return radius * radius / dist / dist;\n"
	"}\n"

	"void main()\n"
	"{\n"
	"	vec2 center1 = vec2(0.5, (sin(time) + 1) / 2);\n"
	"	vec2 center2 = vec2((cos(time * 1.4) + 1) / 2, 0.3);\n"
	"	vec2 center3 = vec2((sin(time) + 1) / 2, (cos(time) + 1) / 2);\n"
	"	vec2 center4 = vec2((cos(time) + 1) / 2.2, (sin(time) + 1) / 2.2);\n"

	"	float color = metal(gl_FragCoord.xy, center1)\n"
	"		+ metal(gl_FragCoord.xy, center2)\n"
	"		+ metal(gl_FragCoord.xy, center3)\n"
	"		+ metal(gl_FragCoord.xy, center4);\n"

	"	if(color > 1)\n"
	"	{\n"
	"		outColor = vec4(0, color, 0, 1);\n"
	"	}\n"
	"	else\n"
	"	{\n"
	"		outColor = vec4(1, 1, 1, 1);\n"
	"	}\n"

	"	if(withinCircle(gl_FragCoord.xy, center1) ||\n"
	"	   withinCircle(gl_FragCoord.xy, center2) ||\n"
	"	   withinCircle(gl_FragCoord.xy, center3) || \n"
	"	   withinCircle(gl_FragCoord.xy, center4))\n"
	"	{\n"
	"		outColor = vec4(1, 0, 0, 1);\n"
	"	}\n"
	"}\n";

int main()
{
	Window window;

	GLShader vertexShader(GL_VERTEX_SHADER);
	vertexShader.fromStr(vert);
	GLShader fragmentShader(GL_FRAGMENT_SHADER);
	fragmentShader.fromStr(frag);
	GLProgram program(vertexShader, fragmentShader);
	program.compile();

	Plane plane(2, 2);
	glGenVertexArrays(1, &plane.vao);
	glBindVertexArray(plane.vao);
	plane.updateAttributes();
	glBindBuffer(GL_ARRAY_BUFFER, plane.getAttribute("position")->buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

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
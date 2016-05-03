#include <engine.h>
using namespace engine;

const char* vert =
	"#version 430 core\n"
	"layout(location = 0) in vec3 position;\n"
	"uniform mat4 model;\n"
	"uniform mat4 view;\n"
	"uniform mat4 project;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = project * view * model * vec4(position, 1);\n"
	"}\n";

const char* frag =
	"#version 430 core\n"
	"out vec4 outColor;\n"
	"uniform vec3 diffuse;\n"
	"void main()\n"
	"{\n"
	"	outColor = vec4(diffuse, 1);\n"
	"}\n";

int main()
{
	Window window;

	GLShader gridVert(GL_VERTEX_SHADER);
	gridVert.fromStr(vert);
	GLShader gridFrag(GL_FRAGMENT_SHADER);
	gridFrag.fromStr(frag);
	GLProgram program(gridVert, gridFrag);
	program.compile();

	GridHelper grid(300, 300, 30, 30);
	glGenVertexArrays(1, &grid.vao);
	glBindVertexArray(grid.vao);
	grid.updateAttributes();

	glBindBuffer(GL_ARRAY_BUFFER, grid.getAttribute("position")->buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	BoxHelper box(50, 50, 50);
	glGenVertexArrays(1, &box.vao);
	glBindVertexArray(box.vao);
	box.updateAttributes();

	glBindBuffer(GL_ARRAY_BUFFER, box.getAttribute("position")->buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	GLuint model = glGetUniformLocation(program.program, "model");
	GLuint view = glGetUniformLocation(program.program, "view");
	GLuint project = glGetUniformLocation(program.program, "project");
	GLuint diffuse = glGetUniformLocation(program.program, "diffuse");

	PerspectiveCamera camera(45.0f, 1.6f, 0.1f, 1000.0f);
	camera.position(0, 30, 30);
	camera.lookAt(Vector3(0, 0, 0));

	Object3D scene;
	Object3D* gridLocation = new Object3D();
	scene.add(gridLocation);
	Object3D* boxLocation = new Object3D();
	boxLocation->position(0, 25, 0);
	scene.add(boxLocation);

	OrbitControl control(camera, window);

	GLRenderer renderer;

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(program.program);

	while (window.active())
	{
		renderer.render(scene, camera);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUniform3f(diffuse, 0.46f, 0.46f, 0.46f);
		glUniformMatrix4fv(model, 1, GL_TRUE, gridLocation->matrix.elements);
		glUniformMatrix4fv(view, 1, GL_TRUE, camera.matrixWorldInverse.elements);
		glUniformMatrix4fv(project, 1, GL_TRUE, camera.projectMatrix.elements);

		glBindVertexArray(grid.vao);
		glDrawArrays(GL_LINES, 0, grid.getAttribute("position")->array.size() / 2);

		glUniform3f(diffuse, 0.35f, 0.35f, 0.35f);
		glUniformMatrix4fv(model, 1, GL_TRUE, boxLocation->matrix.elements);

		glBindVertexArray(box.vao);
		glDrawElements(GL_LINES, box.indices.size(), GL_UNSIGNED_INT, 0);

		window.refresh();
	}

	return 0;
}
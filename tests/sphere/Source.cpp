#include <engine.h>
using namespace engine;

const char* vertexCode =
	"#version 430 core\n"

	"layout(location = 0) in vec3 position;\n"

	"uniform mat4 model;\n"
	"uniform mat4 view;\n"
	"uniform mat4 project;\n"

	"void main()\n"
	"{\n"
	"	gl_Position = project * view * model * vec4(position, 1);\n"
	"}\n";

const char* fragmentCode =
	"#version 430 core\n"

	"uniform vec3 diffuse;\n"
	"out vec4 outColor;\n"

	"void main()\n"
	"{\n"
	"	outColor = vec4(diffuse, 1);\n"
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

	Sphere sphereA(5, 18, 9);
	glGenVertexArrays(1, &sphereA.vao);
	glBindVertexArray(sphereA.vao);
	sphereA.updateAttributes();

	glBindBuffer(GL_ARRAY_BUFFER, sphereA.getAttribute("position")->buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	Sphere sphereB(5, 18, 9, 0, Math::PI * 0.5f);
	glGenVertexArrays(1, &sphereB.vao);
	glBindVertexArray(sphereB.vao);
	sphereB.updateAttributes();

	glBindBuffer(GL_ARRAY_BUFFER, sphereB.getAttribute("position")->buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	Sphere sphereC(5, 18, 9, 0, Math::PI * 0.5f, 0, Math::PI * 0.75f);
	glGenVertexArrays(1, &sphereC.vao);
	glBindVertexArray(sphereC.vao);
	sphereC.updateAttributes();

	glBindBuffer(GL_ARRAY_BUFFER, sphereC.getAttribute("position")->buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	GridHelper grid(100, 100, 20, 20);
	glGenVertexArrays(1, &grid.vao);
	glBindVertexArray(grid.vao);
	grid.updateAttributes();

	glBindBuffer(GL_ARRAY_BUFFER, grid.getAttribute("position")->buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glUseProgram(program.program);
	GLuint modelMatrixLocation = glGetUniformLocation(program.program, "model");
	GLuint viewMatrixLocation = glGetUniformLocation(program.program, "view");
	GLuint projectMatrixLocation = glGetUniformLocation(program.program, "project");
	GLuint diffuseLocation = glGetUniformLocation(program.program, "diffuse");

	PerspectiveCamera camera(45.0f, 1.6f, 0.1f, 1000.0f);
	camera.position(0, 10, 30);
	camera.lookAt(Vector3(0, 0, 0));

	Object3D scene;
	GLRenderer renderer;

	Object3D* a = new Object3D();
	a->position(-5, 0, 5);
	scene.add(a);

	Object3D* b = new Object3D();
	b->position(5, 0, 5);
	scene.add(b);

	Object3D* c = new Object3D();
	c->position(5, 0, -5);
	scene.add(c);

	OrbitControl control(camera, window);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	while (window.active())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.render(scene, camera);

		glUniform3f(diffuseLocation, 0.45f, 0.45f, 0.45f);
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_TRUE, a->matrix.elements);
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_TRUE, camera.matrixWorldInverse.elements);
		glUniformMatrix4fv(projectMatrixLocation, 1, GL_TRUE, camera.projectMatrix.elements);

		glBindVertexArray(grid.vao);
		glDrawArrays(GL_LINES, 0, (GLsizei)grid.getAttribute("position")->array.size() / 2);

		glUniform3f(diffuseLocation, 0.35f, 0.35f, 0.35f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glBindVertexArray(sphereA.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereA.index);
		glDrawElements(GL_TRIANGLES, (GLsizei)sphereA.indices.size(), GL_UNSIGNED_INT, 0);

		glUniformMatrix4fv(modelMatrixLocation, 1, GL_TRUE, b->matrix.elements);
		glBindVertexArray(sphereB.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereB.index);
		glDrawElements(GL_TRIANGLES, (GLsizei)sphereB.indices.size(), GL_UNSIGNED_INT, 0);

		glUniformMatrix4fv(modelMatrixLocation, 1, GL_TRUE, c->matrix.elements);
		glBindVertexArray(sphereC.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereC.index);
		glDrawElements(GL_TRIANGLES, (GLsizei)sphereC.indices.size(), GL_UNSIGNED_INT, 0);

		window.refresh();
	}

	return 0;
}
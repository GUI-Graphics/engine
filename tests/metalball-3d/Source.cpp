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
	Window window("MataBall", 1366, 768);

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

	MetaBall ballA(5);
	MetaBall ballB(4);
	MetaBall ballC(3);

	MarchingCube marchingCube(2, 25);
	marchingCube.addBall(ballA);
	marchingCube.addBall(ballB);
	marchingCube.addBall(ballC);

	GLuint model = glGetUniformLocation(program.program, "model");
	GLuint view = glGetUniformLocation(program.program, "view");
	GLuint project = glGetUniformLocation(program.program, "project");
	GLuint diffuse = glGetUniformLocation(program.program, "diffuse");

	PerspectiveCamera camera(45.0f, (float) window.width / window.height, 0.1f, 1000.0f);
	camera.position(0, 100, 100);
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
		static float time = 0;
		time += 0.03f;

		float c = 4 * cosf(time);

		ballA.position.set(- 8 * cosf(time) - c,  8 * sinf(time) - c, 0);
		ballB.position.set( 12 * sinf(time / 2) + c, 12 * cosf(time / 2) - c, 0);
		ballC.position.set( 10 * cosf(time), 10 * sinf(time), 0);

		renderer.render(scene, camera);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUniform3f(diffuse, 0.46f, 0.46f, 0.46f);
		glUniformMatrix4fv(model, 1, GL_TRUE, gridLocation->matrix.elements);
		glUniformMatrix4fv(view, 1, GL_TRUE, camera.matrixWorldInverse.elements);
		glUniformMatrix4fv(project, 1, GL_TRUE, camera.projectMatrix.elements);

		glBindVertexArray(grid.vao);
		glDrawArrays(GL_LINES, 0, (GLsizei)grid.getAttribute("position")->array.size() / 2);

		glUniform3f(diffuse, 0.35f, 0.35f, 0.35f);
		glUniformMatrix4fv(model, 1, GL_TRUE, boxLocation->matrix.elements);

		glBindVertexArray(box.vao);
		glDrawElements(GL_LINES, (GLsizei)box.indices.size(), GL_UNSIGNED_INT, 0);

		BufferGeometry* surface = marchingCube.createSurface(1);
		glGenVertexArrays(1, &surface->vao);
		glBindVertexArray(surface->vao);
		surface->updateAttributes();

		auto position = surface->getAttribute("position");
		glBindBuffer(GL_ARRAY_BUFFER, position->buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glUniform3f(diffuse, 0.4f, 0.4f, 0.4f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)position->array.size() / 3);

		window.refresh();

		delete surface;
	}

	return 0;
}
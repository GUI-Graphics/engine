#include <engine.h>
using namespace engine;

const char* vertexCode =
	"#version 430 core\n"

	"uniform mat4 model;\n"
	"uniform mat4 view;\n"
	"uniform mat4 project;\n"

	"layout(location = 0) in vec3 position;\n"
	"layout(location = 1) in vec3 normal;\n"

	"out vec3 vNormal;\n"
	"out vec3 vPosition;\n"

	"void main()\n"
	"{\n"
	"	vNormal = mat3(transpose(inverse(model))) * normal;\n"
	"	vPosition = vec3(model * vec4(position, 1));\n"
	"	gl_Position = project * view * model * vec4(position, 1);\n"
	"}\n";

const char* fragmentCode =
	"#version 430 core\n"

	"uniform vec3 color;\n"
	"uniform vec3 lightPosition;\n"
	"uniform vec3 cameraPosition;\n"

	"in vec3 vPosition;\n"
	"in vec3 vNormal;\n"

	"out vec4 outColor;\n"

	"void main()\n"
	"{\n"
	"	vec3 lightDirection = normalize(lightPosition - vPosition);\n"
	"	vec3 viewDirection = normalize(cameraPosition - vPosition);\n"
	"	vec3 reflectDirection = reflect(-lightDirection, vNormal);\n"

	"	vec3 diffuse = color * max(dot(vNormal, lightDirection), 0);\n"
	"	vec3 specular = pow(max(dot(viewDirection, reflectDirection), 0), 32) * vec3(1, 1, 1);\n"
	"	outColor = vec4(color * (0.35f) + diffuse + specular, 1);\n"
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

	TorusKnot torusKnot(7, 3, 360, 24);
	glGenVertexArrays(1, &torusKnot.vao);
	glBindVertexArray(torusKnot.vao);
	torusKnot.updateAttributes();

	glBindBuffer(GL_ARRAY_BUFFER, torusKnot.getAttribute("position")->buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, torusKnot.getAttribute("normal")->buffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	Sphere sphere(10, 72, 36);
	glGenVertexArrays(1, &sphere.vao);
	glBindVertexArray(sphere.vao);
	sphere.updateAttributes();

	glBindBuffer(GL_ARRAY_BUFFER, sphere.getAttribute("position")->buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, sphere.getAttribute("normal")->buffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	Torus torus(10, 3, 72, 36);
	glGenVertexArrays(1, &torus.vao);
	glBindVertexArray(torus.vao);
	torus.updateAttributes();

	glBindBuffer(GL_ARRAY_BUFFER, torus.getAttribute("position")->buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, torus.getAttribute("normal")->buffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	GridHelper grid(200, 200, 20, 20);
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
	GLuint colorLocation = glGetUniformLocation(program.program, "color");
	GLuint lightPositionLocation = glGetUniformLocation(program.program, "lightPosition");
	GLuint cameraPositionLocation = glGetUniformLocation(program.program, "cameraPosition");

	PerspectiveCamera camera(45.0f, 1.6f, 0.1f, 1000.0f);
	camera.position(0, 30, 50);
	camera.lookAt(Vector3(0, 0, 0));

	Object3D scene;
	Object3D* torusKnotLocation = new Object3D();
	scene.add(torusKnotLocation);

	Object3D* sphereLocation = new Object3D();
	sphereLocation->position(-30, 0, 0);
	scene.add(sphereLocation);

	Object3D* torusLocation = new Object3D();
	torusLocation->position(30, 0, 0);
	scene.add(torusLocation);

	GLRenderer renderer;

	OrbitControl control(camera, window);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glUniform3f(lightPositionLocation, 50, 50, 50);

	while (window.active())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.render(scene, camera);

		glUniformMatrix4fv(viewMatrixLocation, 1, GL_TRUE, camera.matrixWorldInverse.elements);
		glUniformMatrix4fv(projectMatrixLocation, 1, GL_TRUE, camera.projectMatrix.elements);

		Vector3 cameraPosition = camera.position();
		glUniform3f(cameraPositionLocation, cameraPosition.x, cameraPosition.y, cameraPosition.z);

		glUniform3f(colorLocation, 0.45f, 0.45f, 0.45f);
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_TRUE, torusKnotLocation->matrix.elements);
		glBindVertexArray(grid.vao);
		glDrawArrays(GL_LINES, 0, (GLsizei)grid.getAttribute("position")->array.size() / 2);

		glUniform3f(colorLocation, 1, 0.35f, 0.35f);
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_TRUE, torusKnotLocation->matrix.elements);
		glBindVertexArray(torusKnot.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, torusKnot.index);
		glDrawElements(GL_TRIANGLES, (GLsizei)torusKnot.indices.size(), GL_UNSIGNED_INT, 0);

		glUniform3f(colorLocation, 0, 0.5f, 1);
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_TRUE, sphereLocation->matrix.elements);
		glBindVertexArray(sphere.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere.index);
		glDrawElements(GL_TRIANGLES, (GLsizei)sphere.indices.size(), GL_UNSIGNED_INT, 0);

		glUniform3f(colorLocation, 0, 1, 0.25f);
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_TRUE, torusLocation->matrix.elements);
		glBindVertexArray(torus.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, torus.index);
		glDrawElements(GL_TRIANGLES, (GLsizei)torus.indices.size(), GL_UNSIGNED_INT, 0);

		window.refresh();
	}

	return 0;
}
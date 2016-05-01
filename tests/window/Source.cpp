#include <engine.h>
using namespace engine;

int main()
{
	Window window;

	GLShader vertex(GL_VERTEX_SHADER);
	vertex.fromFile("vert.glsl");
	GLShader fragment(GL_FRAGMENT_SHADER);
	fragment.fromFile("frag.glsl");
	GLProgram program(vertex, fragment);
	program.compile();

	GLShader phongVertex(GL_VERTEX_SHADER);
	phongVertex.fromFile("phong-vert.glsl");
	GLShader phongFragment(GL_FRAGMENT_SHADER);
	phongFragment.fromFile("phong-frag.glsl");
	GLProgram phongProgram(phongVertex, phongFragment);
	phongProgram.compile();

	PlaneBufferGeometry plane(500, 500, 50, 50);
	glGenVertexArrays(1, &plane.vao);
	glBindVertexArray(plane.vao);

	plane.updateAttributes();

	glBindBuffer(GL_ARRAY_BUFFER, plane.getAttribute("position")->buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	auto planeLocation = new Object3D();

	SphereBufferGeometry sphere(10, 120, 60);
	glGenVertexArrays(1, &sphere.vao);
	glBindVertexArray(sphere.vao);

	sphere.updateAttributes();

	glBindBuffer(GL_ARRAY_BUFFER, sphere.getAttribute("position")->buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, sphere.getAttribute("normal")->buffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	auto sphereLocation = new Object3D();
	sphereLocation->positionY(10.0f);

	SphereBufferGeometry light;
	glGenVertexArrays(1, &light.vao);
	glBindVertexArray(light.vao);

	light.updateAttributes();

	glBindBuffer(GL_ARRAY_BUFFER, light.getAttribute("position")->buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	auto lightLocation = new Object3D();
	lightLocation->position(30.0f, 30.0f, 30.0f);

	glUseProgram(program.program);
	GLuint modelMatrixLocation = glGetUniformLocation(program.program, "modelMatrix");
	GLuint projectMatrixLocation = glGetUniformLocation(program.program, "projectMatrix");
	GLuint viewMatrixLocation = glGetUniformLocation(program.program, "viewMatrix");
	GLuint diffuseLocation = glGetUniformLocation(program.program, "diffuse");

	glUseProgram(phongProgram.program);
	GLuint phongModelMatrixLocation = glGetUniformLocation(phongProgram.program, "modelMatrix");
	GLuint phongProjectMatrixLocation = glGetUniformLocation(phongProgram.program, "projectMatrix");
	GLuint phongViewMatrixLocation = glGetUniformLocation(phongProgram.program, "viewMatrix");
	GLuint phongDiffuseLocation = glGetUniformLocation(phongProgram.program, "diffuse");
	GLuint lightPositionLocation = glGetUniformLocation(phongProgram.program, "lightPosition");
	GLuint cameraPositionLocation = glGetUniformLocation(phongProgram.program, "cameraPositon");

	PerspectiveCamera camera(45.0f, 1.6f, 0.1f, 1000.0f);
	camera.position(0, 50, 100);
	camera.lookAt(Vector3(0, 0, 0));

	Object3D scene;
	scene.add(planeLocation);
	scene.add(sphereLocation);
	scene.add(lightLocation);

	GLRenderer renderer;
	OrbitControl control(camera, window);

	glEnable(GL_DEPTH_TEST);
	
	while (window.active())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.render(scene, camera);

		glBindVertexArray(plane.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, plane.index);

		glUniform3f(diffuseLocation, 0.15f, 0.15f, 0.15f);
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_TRUE, planeLocation->matrix.elements);
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_TRUE, camera.matrixWorldInverse.elements);
		glUniformMatrix4fv(projectMatrixLocation, 1, GL_TRUE, camera.projectMatrix.elements);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, (GLsizei)plane.indices.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(sphere.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere.index);

		glUseProgram(phongProgram.program);

		glUniform3f(phongDiffuseLocation, 1.0f, 0.0f, 0.0f);
		glUniformMatrix4fv(phongModelMatrixLocation, 1, GL_TRUE, sphereLocation->matrix.elements);
		glUniformMatrix4fv(phongViewMatrixLocation, 1, GL_TRUE, camera.matrixWorldInverse.elements);
		glUniformMatrix4fv(phongProjectMatrixLocation, 1, GL_TRUE, camera.projectMatrix.elements);

		glUniform3f(lightPositionLocation, 30.0f, 30.0f, 30.0f);

		Vector3 cameraPosition = camera.position();
		glUniform3f(cameraPositionLocation, cameraPosition.x, cameraPosition.y, cameraPosition.z);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, (GLsizei)sphere.indices.size(), GL_UNSIGNED_INT, 0);

		glUseProgram(program.program);

		glBindVertexArray(light.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, light.index);

		glUniform3f(diffuseLocation, 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_TRUE, lightLocation->matrix.elements);
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_TRUE, camera.matrixWorldInverse.elements);
		glUniformMatrix4fv(projectMatrixLocation, 1, GL_TRUE, camera.projectMatrix.elements);

		glDrawElements(GL_TRIANGLES, (GLsizei)light.indices.size(), GL_UNSIGNED_INT, 0);

		window.refresh();
	}

	for (auto obj : scene.children) delete obj;

	return 0;
}
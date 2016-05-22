#include <engine.h>
#include <SOIL.h>

using namespace engine;

const char* vertexCode =
	"#version 430 core\n"

	"uniform mat4 view;\n"
	"uniform mat4 project;\n"

	"layout(location = 0) in vec3 position;\n"

	"out vec3 uv;\n"

	"void main()\n"
	"{\n"
	"	vec4 pos = project * view * vec4(position * 100, 1);\n"
	"	gl_Position = pos.xyww;\n"
	"	uv = position * 2;\n"
	"}";

const char* fragmentCode =
	"#version 430 core\n"

	"uniform samplerCube church;\n"

	"in vec3 uv;\n"
	"out vec4 outColor;\n"

	"void main()\n"
	"{\n"
	"	outColor = texture(church, uv);\n"
	"}";

int main()
{
	Window window;

	GLShader vertexShader(GL_VERTEX_SHADER);
	vertexShader.fromStr(vertexCode);
	GLShader fragmentShader(GL_FRAGMENT_SHADER);
	fragmentShader.fromStr(fragmentCode);
	GLProgram program(vertexShader, fragmentShader);
	program.compile();

	GLuint beach;
	glGenTextures(1, &beach);
	glBindTexture(GL_TEXTURE_CUBE_MAP, beach);

	int width, height;
	unsigned char* image;

	image = SOIL_load_image("../../resource/beach/posx.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	image = SOIL_load_image("../../resource/beach/negx.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	image = SOIL_load_image("../../resource/beach/posy.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	image = SOIL_load_image("../../resource/beach/negy.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	image = SOIL_load_image("../../resource/beach/posz.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	image = SOIL_load_image("../../resource/beach/negz.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	Box cube;
	glGenVertexArrays(1, &cube.vao);
	glBindVertexArray(cube.vao);
	cube.updateAttributes();

	glBindBuffer(GL_ARRAY_BUFFER, cube.getAttribute("position")->buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glUseProgram(program.program);
	GLuint viewMatrixLocation = glGetUniformLocation(program.program, "view");
	GLuint projectMatrixLocation = glGetUniformLocation(program.program, "project");

	PerspectiveCamera camera(45.0f, 1.6f, 0.1f, 1000.0f);
	camera.position(0, 0, 0.001);
	camera.lookAt(Vector3(0, 0, 0));

	Object3D scene;
	GLRenderer renderer;

	Object3D* cubeLocation = new Object3D();
	scene.add(cubeLocation);

	OrbitControl control(camera, window);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	while (window.active())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.render(scene, camera);
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_TRUE, camera.matrixWorldInverse.elements);
		glUniformMatrix4fv(projectMatrixLocation, 1, GL_TRUE, camera.projectMatrix.elements);

		glDepthFunc(GL_LEQUAL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube.index);
		glDrawElements(GL_TRIANGLES, (GLsizei)cube.indices.size(), GL_UNSIGNED_INT, 0);

		window.refresh();
	}

	glDeleteTextures(1, &beach);
}
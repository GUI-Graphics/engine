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
	"	vec4 pos = project * view * vec4(position * 800, 1);\n"
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

const char* environmentVertex =
	"#version 430 core\n"

	"layout(location = 0) in vec3 position;\n"
	"layout(location = 1) in vec3 normal;\n"

	"out vec3 vNormal;\n"
	"out vec3 vPosition;\n"

	"uniform mat4 model;\n"
	"uniform mat4 view;\n"
	"uniform mat4 project;\n"

	"void main()\n"
	"{\n"
	"	gl_Position = project * view * model * vec4(position, 1);\n"
	"	vNormal = mat3(transpose(inverse(model))) * normal;\n"
	"	vPosition = vec3(model * vec4(position, 1));\n"
	"}\n";

const char* environmentFragment =
	"#version 430 core\n"

	"in vec3 vPosition;\n"
	"in vec3 vNormal;\n"
	"out vec4 outColor;\n"

	"uniform vec3 cameraPosition;\n"
	"uniform samplerCube cubemap;\n"

	"void main()\n"
	"{\n"
	"	vec3 incident = normalize(vPosition - cameraPosition);\n"
	"	vec3 r = reflect(incident, vNormal);\n"
	"	outColor = texture(cubemap, r);\n"
	"}\n";

GLuint loadCubemap(std::string name)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int width, height;
	unsigned char* image;
	std::string base = "../../resource/";

	image = SOIL_load_image((base + name + "/posx.jpg").c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	image = SOIL_load_image((base + name + "/negx.jpg").c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	image = SOIL_load_image((base + name + "/posy.jpg").c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	image = SOIL_load_image((base + name + "/negy.jpg").c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	image = SOIL_load_image((base + name + "/posz.jpg").c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	image = SOIL_load_image((base + name + "/negz.jpg").c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return texture;
}

GLProgram* loadProgram(const char* vert, const char* frag)
{
	GLShader vertexShader(GL_VERTEX_SHADER);
	vertexShader.fromStr(vert);
	GLShader fragmentShader(GL_FRAGMENT_SHADER);
	fragmentShader.fromStr(frag);

	GLProgram* program = new GLProgram(vertexShader, fragmentShader);
	program->compile();

	return program;
}

int main()
{
	Window window;

	GLProgram* cubemapProgram = loadProgram(vertexCode, fragmentCode);
	GLProgram* environmentProgram = loadProgram(environmentVertex, environmentFragment);

	GLuint beach = loadCubemap("church");

	Box cube;
	glGenVertexArrays(1, &cube.vao);
	glBindVertexArray(cube.vao);
	cube.updateAttributes();

	glBindBuffer(GL_ARRAY_BUFFER, cube.getAttribute("position")->buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	TorusKnot torusKnot(3, 1.4f, 360, 24);
	glGenVertexArrays(1, &torusKnot.vao);
	glBindVertexArray(torusKnot.vao);
	torusKnot.updateAttributes();

	glBindBuffer(GL_ARRAY_BUFFER, torusKnot.getAttribute("position")->buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, torusKnot.getAttribute("normal")->buffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	GLuint viewMatrixLocation = glGetUniformLocation(cubemapProgram->program, "view");
	GLuint projectMatrixLocation = glGetUniformLocation(cubemapProgram->program, "project");

	GLuint model = glGetUniformLocation(environmentProgram->program, "model");
	GLuint view = glGetUniformLocation(environmentProgram->program, "view");
	GLuint project = glGetUniformLocation(environmentProgram->program, "project");
	GLuint cameraPosition = glGetUniformLocation(environmentProgram->program, "cameraPosition");

	PerspectiveCamera camera(45.0f, 1.6f, 0.1f, 1000.0f);
	camera.position(0, 10, 10);
	camera.lookAt(Vector3(0, 0, 0));

	Object3D scene;
	GLRenderer renderer;

	Object3D* torusKnotLocation = new Object3D();
	scene.add(torusKnotLocation);

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

		glDepthFunc(GL_LESS);
		glUseProgram(environmentProgram->program);
		glBindVertexArray(torusKnot.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, torusKnot.index);
		glDrawElements(GL_TRIANGLES, (GLsizei)torusKnot.indices.size(), GL_UNSIGNED_INT, 0);

		glUniformMatrix4fv(model, 1, GL_TRUE, torusKnotLocation->matrix.elements);
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_TRUE, camera.matrixWorldInverse.elements);
		glUniformMatrix4fv(projectMatrixLocation, 1, GL_TRUE, camera.projectMatrix.elements);


		Vector3 cameraPos = camera.position();
		glUniform3f(cameraPosition, cameraPos.x, cameraPos.y, cameraPos.z);

		glDepthFunc(GL_LEQUAL);
		glUseProgram(cubemapProgram->program);
		glBindVertexArray(cube.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube.index);
		glDrawElements(GL_TRIANGLES, (GLsizei)cube.indices.size(), GL_UNSIGNED_INT, 0);

		window.refresh();
	}

	glDeleteTextures(1, &beach);
}
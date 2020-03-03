#include "Engine.h"

#define numVAOs 1
#define numObjects 1

GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numObjects];

glm::mat4 ortho;

float x = 0.0f, inc = 0.01f;

std::string Engine::ReadShaderSource(const char* filepath) {
	std::string content;
	std::ifstream fileStream(filepath, std::ios::in);
	std::string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content.c_str();
}

//function to add a quad to the scene
void AddQuad(glm::vec2 size) {

	float h_width = size.x / 2.0f;
	float h_height = size.y / 2.0f;

	float vertices[18] = {
		-h_width, h_height, 1.0f,
		h_width, h_height, 1.0f,
		-h_width, -h_height, 1.0f,
		-h_width, -h_height, 1.0f,
		h_width, h_height, 1.0f,
		h_width, -h_height, 1.0f
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Engine::Init(GLFWwindow* window) {
	ortho = glm::ortho(0.0f, (float)800, (float)600, 0.0f, 0.0f, 100.0f);
	renderingProgram = createShaderProgram("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numObjects, vbo);
	AddQuad(glm::vec2(2.5f, 2.5f));
}

void Engine::Display(GLFWwindow* window, double currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	x += inc;
	if (x > 1.0f) inc = -0.01f;
	if (x < -1.0f) inc = 0.01f;

	GLuint orthoLoc = glGetUniformLocation(renderingProgram, "ortho");

	GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset");
	glProgramUniform1f(renderingProgram, offsetLoc, x);
	glUniformMatrix4fv(orthoLoc, 1, GL_FALSE, glm::value_ptr(ortho));

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

GLuint Engine::createShaderProgram(const char* vs, const char* fs) {
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vshade = ReadShaderSource(vs);
	std::string fshade = ReadShaderSource(fs);

	const char* vshaderSource = vshade.c_str(); //these calls dont work yet :/
	const char* fshaderSource = fshade.c_str();

	glShaderSource(vShader, 1, &vshaderSource, NULL);
	glShaderSource(fShader, 1, &fshaderSource, NULL);
	glCompileShader(vShader);
	glCompileShader(fShader);

	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);

	return vfProgram;
}

int Engine::main() {
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Cody's Engine", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		exit(EXIT_FAILURE);
	}
	glfwSwapInterval(1);

	Init(window);

	while (!glfwWindowShouldClose(window)) {
		Display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

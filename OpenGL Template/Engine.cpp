#include "Engine.h"

#define numVAOs = 1;

GLuint renderingProgram;
GLuint vao[1];

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

void Engine::Init(GLFWwindow* window) {
	renderingProgram = createShaderProgram();
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
}

void Engine::Display(GLFWwindow* window, double currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);

	x += inc;
	if (x > 1.0f) inc = -0.01f;
	if (x < -1.0f) inc = 0.01f;

	GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset");
	glProgramUniform1f(renderingProgram, offsetLoc, x);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

GLuint Engine::createShaderProgram() {
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vshade = ReadShaderSource("Shaders/vertexShader.glsl");
	std::string fshade = ReadShaderSource("Shaders/fragmentShader.glsl");

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
	GLFWwindow* window = glfwCreateWindow(600, 600, "Cody's Engine", NULL, NULL);
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

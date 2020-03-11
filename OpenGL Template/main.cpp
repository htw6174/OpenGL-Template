#include "main.h"
#include "Utils.h"
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

GLuint createShaderProgram() 
{
	GLint vertCompiled;
	GLint fragCompiled;
	GLint linked;

	const char* vshaderSource =
		"#version 430 \n"
		"void main(void) \n"
		"{gl_Position = vec4(0.0,0.0,0.0,1.0);}";
	const char* fshaderSource = 
		"#version 430 \n"
		"out vec4 color; \n"
		"void main(void) \n"
		"{ if (gl_FragCoord.x < 300) color=vec4(1.0, 0.0, 0.0, 1.0); else color=vec4(0.0, 0.0, 1.0, 1.0);\n}";

	// Catch Errors while compiling Shaders
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vshaderSource, NULL);
	glCompileShader(vShader);
	Utils::checkOpenGLError();
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1) 
	{
		cout << "Vertex Compilation Failed!" << endl;
		Utils::printShaderLog(vShader);
	}

	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fshaderSource, NULL);
	glCompileShader(fShader);
	Utils::checkOpenGLError();
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
	if (fragCompiled != 1) 
	{
		cout << "Fragment Compilation Failed!" << endl;
		Utils::printShaderLog(fShader);
	}

	// Catch Errors while linking Shaders
	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);
	Utils::checkOpenGLError();

	glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
	if (linked != 1) 
	{
		cout << "Linking Failed!" << endl;
		Utils::printProgramLog(vfProgram);
	}
	return vfProgram;
}

void init(GLFWwindow* window) 
{
	renderingProgram = createShaderProgram();
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);

}

void display(GLFWwindow* window, double currentTime) 
{


	glClearColor(0.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);
	glPointSize(50.0f);
	glDrawArrays(GL_POINTS, 0, 1);

}

int main(void) 
{
	cout << "Hello World!" << endl;
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter 2 - program 2", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		exit(EXIT_FAILURE);
	}
	glfwSwapInterval(1);

	init(window);

	while (!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
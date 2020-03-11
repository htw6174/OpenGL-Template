#include "main.h"
#include "Utils.h"
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];
float x = 0.0f;
float inc = 0.01f;


GLuint createShaderProgram() 
{
	GLint vertCompiled;
	GLint fragCompiled;
	GLint linked;

	string vertShaderString = Utils::readShaderSource("vertShader.glsl");
	string fragShaderString = Utils::readShaderSource("fragShader.glsl");

	const char* vertShaderSource = vertShaderString.c_str();
		
	const char* fragShaderSource = fragShaderString.c_str();

	// Catch Errors while compiling Shaders
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vertShaderSource, NULL);
	glCompileShader(vShader);
	Utils::checkOpenGLError();
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1) 
	{
		cout << "Vertex Compilation Failed!" << endl;
		Utils::printShaderLog(vShader);
	}

	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fragShaderSource, NULL);
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
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	x += inc; // move triangle along x
	if (x > 1.0f) inc = -0.01f;
	if (x < -1.0f) inc = 0.01f;

	GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset"); // get ptr to 'offset' uniform variable in the vert shader
	glProgramUniform1f(renderingProgram, offsetLoc, x);
	glDrawArrays(GL_TRIANGLES, 0, 3);

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
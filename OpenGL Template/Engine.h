#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <iostream>

#pragma once
class Engine
{

public:
	int main();

private:
	std::string ReadShaderSource(const char*);
	void Init(GLFWwindow*);
	void Display(GLFWwindow*, double);
	GLuint createShaderProgram(const char* vs, const char* fs);
};


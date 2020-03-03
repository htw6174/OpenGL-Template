#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
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


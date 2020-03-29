#pragma once
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Utils.h"

class Renderer {

#define numVAOs 1
#define numVBOs 2

private:
	GLFWwindow* window;
	int ScreenWidth, ScreenHeight;
	float cameraX, cameraY, cameraZ;
	float cubeLocX, cubeLocY, cubeLocZ;
	GLuint renderingProgram;
	GLuint vao[numVAOs];
	GLuint vbo[numVBOs];

	// allocate variables used in display() to avoid allocating them every frame
	GLuint vLoc, projLoc, timeOffsetLoc;
	int width, height;
	float aspect, timeOffset;
	glm::mat4 pMat, vMat, mMat, tMat, rMat, mvMat;

public:
	Renderer(int, int);
	void Init(GLFWwindow*);
	void Start();
	void Display(GLFWwindow*, double);
	void Render();
	void window_size_callback(GLFWwindow*, int, int);
	void SetupVertices();
	void Exit();
};
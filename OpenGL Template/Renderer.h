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

public:
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
	void Init();
	void Start();
	void Render();
	void Exit();
private:
	void Display();
	void SetupVertices();
};
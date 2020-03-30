#include "main.h"
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <stack>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Utils.h"
using namespace std;

#define numVAOs 1
#define numVBOs 2

float cameraX, cameraY, cameraZ;
float astLocX, astLocY, astLocZ;
float shipLocX, shipLocY, shipLocZ;
float shipRotZ;
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

// allocate variables used in display() to avoid allocating them every frame
GLuint mvLoc, projLoc, timeOffsetLoc;
int width, height;
float aspect, timeOffset;
glm::mat4 pMat, vMat, mMat, tMat, rMat, mvMat;
stack<glm::mat4> mvStack;

//timing
double lastFrameTime;
double deltaTime;

const float XBOUND = 10.0f;
const float YBOUND = 10.0f;

int forwardPressed = 0;
int rotateRightPressed = 0;
int rotateLeftPressed = 0;

glm::vec3 shipHeading;


void setupVertices(void) 
{
	// 2x2x2 cube at origin
	float vertexPositions[108] = 
	{
		-1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f, 1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f, 1.0f, -1.0f,  1.0f, 1.0f,  1.0f, -1.0f,
		1.0f, -1.0f,  1.0f, 1.0f,  1.0f,  1.0f, 1.0f,  1.0f, -1.0f,
		1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f, 1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, 1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f, 1.0f,  1.0f, -1.0f, 1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f
	};

	//Pyramid with 18 vertices comprising 6 triangles (4 tri sides + 2 tri on bottom)
	float pyramidPositions[54] =
	{ -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,    //front
		1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,    //right
		1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  //back
		-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,  //left
		-1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, //LF
		1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f  //RR
	};

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidPositions), pyramidPositions, GL_STATIC_DRAW);
}


void init(GLFWwindow* window)
{
	renderingProgram = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");

	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 10.0f;
	astLocX = 1.0f; astLocY = 2.0f; astLocZ = 0.0f;
	shipLocX = 1.0f; shipLocY = 1.0f; shipLocZ = 0.0f;

	setupVertices();
}

void window_size_callback(GLFWwindow* win, int newWidth, int newHeight) {
	aspect = (float)newWidth / (float)newHeight;
	glViewport(0, 0, newWidth, newHeight);
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}

void display(GLFWwindow* window, double currentTime, double deltaTime) 
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	// get uniform variables for the v and projection matrices
	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

	// build view matrix
	//vMat = glm::lookAt(glm::vec3(cameraX, cameraY, cameraZ), glm::vec3(shipLocX, shipLocY, shipLocZ), glm::vec3(0.0, 1.0, 0.0));
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	// push the view matrix onto the stack first
	mvStack.push(vMat);

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	// PYRAMID PLAYER IN CENTER
	forwardPressed = glfwGetKey(window, GLFW_KEY_W);
	if (forwardPressed == GLFW_PRESS)
	{		
		shipLocX += 0.04f * cos(shipRotZ + glm::pi<float>()/2.0f);
		shipLocY += 0.04f * sin(shipRotZ + glm::pi<float>() / 2.0f);
	}

	rotateRightPressed = glfwGetKey(window, GLFW_KEY_E);
	rotateLeftPressed = glfwGetKey(window, GLFW_KEY_Q);
	if (rotateRightPressed == GLFW_PRESS) {
		shipRotZ -= 0.04f;
	}
	else if (rotateLeftPressed) {
		shipRotZ += 0.04f;
	}
	
	// push a copy of whats on top
	mvStack.push(mvStack.top());
	// apply the PLAYER's position matrix to the stack -> (0,0,0) origin
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(shipLocX, shipLocY, shipLocZ));
	mvStack.top() *= rotate(glm::mat4(1.0f), shipRotZ, glm::vec3(0.0f, 0.0f, 1.0f));

	//mvStack.top() *= rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
	mvStack.top() *= scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.25f));

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	//back-face culling enable
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, 18);

	// pop the players transform matrix (TRS)
	mvStack.pop();

	// Small cube is asteroid
	astLocX += 0.01f;//100000.0f * deltaTime;
	if (astLocX > XBOUND)
	{
		astLocX = -XBOUND;
	}
	else if (astLocX < -XBOUND) 
	{
		astLocX = XBOUND;
	}
	astLocY += 0.03f;//50000.0f * deltaTime;
	if (astLocY > YBOUND)
	{
		astLocY = -YBOUND;
	}
	else if (astLocY < -YBOUND)
	{
		astLocY = YBOUND;
	}

	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(astLocX, astLocY, astLocZ));
	mvStack.top() *= rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(1.0, 1.0, 0.0));
	mvStack.top() *= scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(0);
	//back-face culling enable
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	mvStack.pop();

	// pop the view matrix
	mvStack.pop();  // the final pop is for the view matrix
}

int main(void) 
{
	cout << "Hello World!" << endl;
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600, "CUBE AND PYRAMID!", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		exit(EXIT_FAILURE);
	}
	glfwSwapInterval(1);

	glfwSetWindowSizeCallback(window, window_size_callback);

	init(window);

	Utils::checkOpenGLError();
	Utils::printShaderLog(renderingProgram);
	Utils::printProgramLog(renderingProgram);
	
	while (!glfwWindowShouldClose(window)) {
		deltaTime = glfwGetTime() - lastFrameTime;
		if (deltaTime > 0.0001f) {
			deltaTime = 0.0f;
		}
		display(window, glfwGetTime(), deltaTime);
		glfwSwapBuffers(window);
		glfwPollEvents();
		lastFrameTime = glfwGetTime();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

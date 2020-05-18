#pragma once

#include <GL\glew.h>

class MeshUtils
{
public:
	static GLuint LoadFromFile(char* filename);
	static GLuint LoadFromArray(float* vertices, int size);
	static GLuint LoadFromArrayTextured(float* vertices, int size, const char* textPath);
};


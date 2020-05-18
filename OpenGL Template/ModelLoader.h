#pragma once

#include <GL\glew.h>

class ModelLoader
{
public:
	static GLuint LoadFromFile(char* filename);
	static GLuint LoadFromArray(float* vertices, int size);
};


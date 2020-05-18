#include "MeshUtils.h"
#include "Utils.h"

GLuint MeshUtils::LoadFromFile(char* filename)
{
	// TODO: Load from filename, automatically determine size
	return GLuint();
}

GLuint MeshUtils::LoadFromArray(float* vertices, int size)
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	return vao;
}

GLuint MeshUtils::LoadFromArrayTextured(float* vertices, int size, const char* textPath) {
	
	//GLuint texture = Utils::loadTexture(textPath);
	
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
	return vao;
}
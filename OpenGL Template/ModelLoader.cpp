#include "ModelLoader.h"

GLuint ModelLoader::LoadFromFile(char* filename)
{
	// TODO: Load from filename, automatically determine size
	return GLuint();
}

GLuint ModelLoader::LoadFromArray(float* vertices, int size)
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

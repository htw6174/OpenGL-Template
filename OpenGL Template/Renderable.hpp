#pragma once

#include "Component.hpp"
#include <glm\glm.hpp>
#include <GL\glew.h>

struct Renderable : Component
{
	GLuint VAO = 0;
	GLuint renderingProgram;
	glm::vec3 color;
	const char* FragShader;
	const char* VertShader;
	const char* Texture;

	// GL options
	GLenum windingOrder = GL_CCW;
};
#pragma once

#include "Component.hpp"
#include <glm\glm.hpp>
#include "GL/glew.h"

struct Renderable : Component
{
	GLuint VAO = 0;
	GLuint renderingProgram;
	glm::vec3 tint = glm::vec3(1., 0., 1.);

	// GL options
	GLenum windingOrder = GL_CCW;
	GLenum primitiveType = GL_TRIANGLES;
};
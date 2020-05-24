#pragma once

#include "Component.hpp"
#include <glm/glm.hpp>

struct Asteroid : Component
{
public:
	glm::vec3 velocity;
	glm::vec3 rotationalVelocity;

};
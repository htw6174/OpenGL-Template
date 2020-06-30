#pragma once

#include "Component.hpp"
#include <glm\glm.hpp>


struct BoxCollider : Component {
public:
	glm::vec3 centerOffset = glm::vec3(0);
	glm::vec3 boundingBox = glm::vec3(1);
};
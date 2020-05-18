#pragma once

#include "Component.hpp"
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

struct Camera : Component
{
	glm::mat4x4 projectionTransform;

	static glm::mat4x4 MakeProjectionTransform(float fov, float nearClip, float farClip, unsigned int viewWidth, unsigned int viewHeight)
	{
		float aspect = (float)viewWidth / (float)viewHeight;
		return glm::perspective(fov, aspect, nearClip, farClip);
	}
};
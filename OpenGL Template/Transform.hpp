#pragma once

#include "Component.hpp"
#include <glm\glm.hpp>
#include <glm\gtx\euler_angles.hpp>
#include <glm\gtc\quaternion.hpp>

struct Transform : Component
{
private:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

public:
	glm::vec3 GetPosition()
	{
		return this->position;
	}

	void SetPosition(glm::vec3 position)
	{
		this->position = position;
	}

	void SetPosition(float x, float y, float z)
	{
		this->position = glm::vec3(x, y, z);
	}

	void Translate(glm::vec3 delta)
	{
		this->position += delta;
	}

	glm::vec3 GetRotationEulerAngles()
	{
		return glm::eulerAngles(this->rotation);
	}
		
	glm::quat GetRotation()
	{
		return this->rotation;
	}

	void SetRotationEulerAngles(glm::vec3 eulerAngles)
	{
		this->rotation = glm::quat(eulerAngles);
	}

	void RotateByDegrees(float degrees, glm::vec3 axis)
	{
		RotateByRadians(glm::radians(degrees), axis);
	}

	void RotateByRadians(float radians, glm::vec3 axis)
	{
		this->rotation *= glm::angleAxis(radians, glm::normalize(axis));
		this->rotation.w = glm::clamp(this->rotation.w, -1.0f, 1.0f);
	}

	glm::vec3 GetScale()
	{
		return this->scale;
	}

	void SetScale(glm::vec3 scale)
	{
		this->scale = scale;
	}
};
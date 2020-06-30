#pragma once

#include "Utils.h"

#include "System.hpp"
#include "Renderable.hpp"
#include "Camera.hpp"
#include "Renderable.hpp"
#include "Transform.hpp"
#include "Coordinator.hpp"

#include <memory>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <cmath>

class RenderSystem : public System
{
public:
	Entity mCamera;

	void SetProjection(glm::mat4);

	void Init() override;

	void Update(float deltaTime) override;

private:
	GLuint mvLoc, projLoc, tintLoc, objectIdLoc;

	glm::mat4 pMat, vMat, mMat, mvMat;
};
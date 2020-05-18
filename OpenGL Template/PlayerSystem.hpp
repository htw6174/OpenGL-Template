#pragma once

#include "Player.hpp"
#include "Transform.hpp"

#include "System.hpp"
#include "Coordinator.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class PlayerSystem : public System
{
private:
	static void PlayerMovementCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
public:
	static bool moveForward;
	static bool rotateLeft;
	static bool rotateRight;
	void Init() override;
	void Update(float deltaTime) override;
};


#pragma once

#include "Transform.hpp"
#include "MeshUtils.h"
#include "Shapes.hpp"
#include "Renderable.hpp"
#include "BoxCollider.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Utils.h"

#include "System.hpp"
#include "Coordinator.hpp"
#include "RenderSystem.hpp"
#include "BoxColliderSystem.hpp"
#include "BulletSystem.hpp"

#include <GLFW/glfw3.h>

class PlayerSystem : public System
{
private:
	static void PlayerInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
public:
	static bool moveForward;
	static bool rotateLeft;
	static bool rotateRight;
	static bool firing;
	void Init() override;
	void Update(float deltaTime) override;
	void FireBullet(Transform& transform);
};


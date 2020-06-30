#pragma once

#include "Asteroid.hpp"

#include "BoxColliderSystem.hpp"
#include "Transform.hpp"
#include "Player.hpp"
#include "Camera.hpp"

#include "System.hpp"
#include "Coordinator.hpp"
#include "ShaderUtils.h"

#include <cmath>

class AsteroidSystem : public System
{
public:
	void Init() override;
	void Update(float deltaTime) override;
	static void CollisionCallback(Entity owner, Entity other);
	Entity PlayerEntity;
};

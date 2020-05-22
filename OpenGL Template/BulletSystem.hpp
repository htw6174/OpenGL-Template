#pragma once

#include "Coordinator.hpp"


class BulletSystem : public System
{
public:
	std::set<Entity> bulletsToDestroy;

	void Init() override;

	void Update(float deltaTime) override;
};
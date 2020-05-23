#pragma once

#include "System.hpp"

class AsteroidSpawnerSystem : System
{
	void Init() override;

	void Update(float deltaTime) override;
};
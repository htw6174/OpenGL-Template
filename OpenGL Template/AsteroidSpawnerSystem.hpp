#pragma once

#include "System.hpp"

class AsteroidSpawnerSystem : public System
{
public:
	void Init() override;

	void Update(float deltaTime) override;
private:
	float spawnCounter;

};
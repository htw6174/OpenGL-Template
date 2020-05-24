#pragma once

#include "Renderable.hpp"
#include "Transform.hpp"
#include "AsteroidSpawner.hpp"

#include "MeshUtils.h"
#include "Shapes.hpp"

#include "System.hpp"
#include "Coordinator.hpp"
#include "RenderSystem.hpp"

#include <cstdlib>
#include <ctime>

class AsteroidSpawnerSystem : public System
{
public:
	void Init() override;

	void Update(float deltaTime) override;
private:
	float spawnCounter;
	void SpawnAsteroid();
};
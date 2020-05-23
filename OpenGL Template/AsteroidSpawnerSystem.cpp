#include "AsteroidSpawnerSystem.hpp"

#include "Coordinator.hpp"
#include "Transform.hpp"
#include "AsteroidSpawner.hpp"

extern Coordinator gCoordinator;

void AsteroidSpawnerSystem::Init()
{
	spawnCounter = 0.0;
}

void AsteroidSpawnerSystem::Update(float deltaTime)
{
	for (auto const& entity : mEntities)
	{
		auto& spawnerTransform = gCoordinator.GetComponent<Transform>(entity);
		auto& asteroidSpawner = gCoordinator.GetComponent<AsteroidSpawner>(entity);
		spawnCounter += deltaTime;
		if (spawnCounter > asteroidSpawner.Period)
		{
			//spawn asteroid


			spawnCounter = 0.0f;
		}
	}
}

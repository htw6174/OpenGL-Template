#include "AsteroidSystem.hpp"

extern Coordinator gCoordinator;
extern std::shared_ptr<BoxColliderSystem> boxColliderSystem;

void AsteroidSystem::Init()
{
	for (auto const& entity : mEntities)
	{
		
	}
}

void AsteroidSystem::Update(float deltaTime)
{
	for (auto const& entity : mEntities)
	{
		auto& asteroidTransform = gCoordinator.GetComponent<Transform>(entity);
		auto& asteroidComponent = gCoordinator.GetComponent<Asteroid>(entity);


		asteroidTransform.Translate(asteroidComponent.velocity * deltaTime);

		if (asteroidTransform.GetPosition().x > 15.0f)
		{
			asteroidTransform.Translate(glm::vec3(-30.0, 0., 0.));
		}
		if (asteroidTransform.GetPosition().x < -15.0f)
		{
			asteroidTransform.Translate(glm::vec3(30.0, 0., 0.));
		}

		if (asteroidTransform.GetPosition().y > 15.0f)
		{
			asteroidTransform.Translate(glm::vec3( 0., -30.0, 0.));
		}	
		if (asteroidTransform.GetPosition().y < -15.0f)
		{
			asteroidTransform.Translate(glm::vec3(0., 30.0, 0.));
		}

	}
}

void AsteroidSystem::CollisionCallback(Entity owner, Entity other)
{
	//std::cout << "In Asteroid System: Entity " << owner << " collided with entity " << other << std::endl;

	if (!gCoordinator.HasComponent<Asteroid>(other))
	{
		gCoordinator.DestroyEntity(owner);
	}
}

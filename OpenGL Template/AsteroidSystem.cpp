
#include "AsteroidSystem.hpp"

extern Coordinator gCoordinator;

void AsteroidSystem::Init()
{
	
}

void AsteroidSystem::Update(float deltaTime)
{
	for (auto const& entity : mEntities)
	{
		auto& asteroidTransform = gCoordinator.GetComponent<Transform>(entity);
		auto& asteroidComponent = gCoordinator.GetComponent<Asteroid>(entity);


		asteroidTransform.Translate(asteroidComponent.velocity * deltaTime);

		if (asteroidTransform.GetPosition().x > 12.0f)
		{
			asteroidTransform.Translate(glm::vec3(-24.0, 0., 0.));
		}
		if (asteroidTransform.GetPosition().x < -12.0f)
		{
			asteroidTransform.Translate(glm::vec3(24.0, 0., 0.));
		}

		if (asteroidTransform.GetPosition().y > 12.0f)
		{
			asteroidTransform.Translate(glm::vec3( 0., -24.0, 0.));
		}	
		if (asteroidTransform.GetPosition().y < -12.0f)
		{
			asteroidTransform.Translate(glm::vec3(0., 24.0, 0.));
		}

	}
}

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
	Transform& playerTransform = gCoordinator.GetComponent<Transform>(PlayerEntity);
	glm::vec3 playerPosition = playerTransform.GetPosition();
	GLuint lightPos = glGetUniformLocation(ShaderUtils::ShaderMap["Asteroid"], "lightPos");
	glUniform3fv(lightPos, 1, glm::value_ptr(playerPosition));

	for (auto const& entity : mEntities)
	{
		auto& asteroidTransform = gCoordinator.GetComponent<Transform>(entity);
		auto& asteroidComponent = gCoordinator.GetComponent<Asteroid>(entity);


		asteroidTransform.Translate(asteroidComponent.velocity * deltaTime);
		asteroidTransform.RotateByDegrees(asteroidComponent.rotationSpeed * deltaTime, asteroidComponent.rotationAxis);

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

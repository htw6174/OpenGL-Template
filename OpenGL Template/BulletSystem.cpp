#include "BulletSystem.hpp"
#include "Coordinator.hpp"
#include "Transform.hpp"
#include "Bullet.hpp"

extern Coordinator gCoordinator;

void BulletSystem::Init()
{
	
}

void BulletSystem::Update(float deltaTime)
{
	for (auto const& entity : mEntities)
	{
		auto& bulletTransform = gCoordinator.GetComponent<Transform>(entity);
		auto& bulletComponent = gCoordinator.GetComponent<Bullet>(entity);

		bulletTransform.Translate(
			glm::vec3(
				bulletComponent.speed * deltaTime * cos(bulletTransform.GetRotationEulerAngles().z + glm::pi<float>() / 2.0f),
				bulletComponent.speed * deltaTime * sin(bulletTransform.GetRotationEulerAngles().z + glm::pi<float>() / 2.0f),
				0.0f
			)
		);

		bulletComponent.lifetime -= 0.1f;
		if (bulletComponent.lifetime < 0)
		{
			bulletsToDestroy.emplace(entity);
		}
	}

	if (bulletsToDestroy.size() > 0)
	{
		for (auto& bullet : bulletsToDestroy)
		{	
			gCoordinator.DestroyEntity(bullet);
		}
		bulletsToDestroy.clear();
	}
}

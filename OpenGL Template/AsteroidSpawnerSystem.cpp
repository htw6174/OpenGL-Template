#include "AsteroidSpawnerSystem.hpp"

extern Coordinator gCoordinator;
extern std::shared_ptr <BoxColliderSystem> boxColliderSystem;

void AsteroidSpawnerSystem::Init()
{
	srand(time(0));
	spawnTimer = 0.0;
}

void AsteroidSpawnerSystem::Update(float deltaTime)
{
	for (auto const& entity : mEntities)
	{
		auto& spawnerTransform = gCoordinator.GetComponent<Transform>(entity);
		auto& asteroidSpawner = gCoordinator.GetComponent<AsteroidSpawner>(entity);

		spawnTimer += deltaTime;
		if (spawnTimer > asteroidSpawner.Period && asteroidSpawner.CurrentCount<asteroidSpawner.MaxCount)
		{
			float randPosX = -14.999999f;//static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 10;
			float randPosY = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 20 - 10;
			float randVelX = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 8 - 4;
			float randVelY = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 8 - 4;

			//spawn asteroid
			SpawnAsteroid(glm::vec3(randPosX, randPosY, 0.f), glm::vec3(randVelX, randVelY, 0.0f), glm::vec3(0.f, 0.f, 0.0f));

			spawnTimer = 0.0f;
			asteroidSpawner.CurrentCount++;
		}
	}
}

void AsteroidSpawnerSystem::SpawnAsteroid(glm::vec3 position, glm::vec3 initialVelocity, glm::vec3 initialRotationalVeclocity)
{
	Entity asteroid = gCoordinator.CreateEntity();

	Transform asteroidTransform = Transform();

	asteroidTransform.SetPosition(position);
	
	gCoordinator.AddComponent<Transform>(
		asteroid,
		asteroidTransform
	);

	Renderable asteroidRenderable = Renderable();
	asteroidRenderable.VAO = MeshUtils::LoadFromArray(cubeVertexPositions, 108);
	asteroidRenderable.windingOrder = GL_CW;
	asteroidRenderable.renderingProgram = ShaderUtils::ShaderMap["Asteroid"];
	asteroidRenderable.tint = glm::vec3(.5, .05, 0.);
	gCoordinator.AddComponent<Renderable>(
		asteroid,
		asteroidRenderable
	);

	//  Add BoxCollider
	BoxCollider asteroidBoxCollider = BoxCollider();
	asteroidBoxCollider.boundingBox = glm::vec3(2.0);
	gCoordinator.AddComponent<BoxCollider>(
		asteroid,
		asteroidBoxCollider
		);


	// Add Asteroid Component
	Asteroid asteroidComponent = Asteroid();
	asteroidComponent.velocity = initialVelocity;
	asteroidComponent.rotationalVelocity = initialRotationalVeclocity;
	gCoordinator.AddComponent<Asteroid>(
		asteroid,
		asteroidComponent
	);

	boxColliderSystem->Subscribe(asteroid, AsteroidSystem::CollisionCallback);
}

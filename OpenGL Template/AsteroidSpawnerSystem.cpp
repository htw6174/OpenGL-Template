#include "AsteroidSpawnerSystem.hpp"

extern Coordinator gCoordinator;
extern std::shared_ptr <RenderSystem> renderSystem;

void AsteroidSpawnerSystem::Init()
{
	srand(time(0));
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
			SpawnAsteroid();

			spawnCounter = 0.0f;
		}
	}
}

void AsteroidSpawnerSystem::SpawnAsteroid()
{
	Entity asteroid = gCoordinator.CreateEntity();

	Transform asteroidTransform = Transform();
	// Setup random rotation and scale
	float randX = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float randY = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	asteroidTransform.SetPosition(randX * 20 - 10, randY * 20 - 10, 0.0f);
	
	gCoordinator.AddComponent<Transform>(
		asteroid,
		asteroidTransform
	);

	Renderable asteroidRenderable = Renderable();
	asteroidRenderable.VAO = MeshUtils::LoadFromArray(cubeVertexPositions, 108);
	asteroidRenderable.windingOrder = GL_CW;
	asteroidRenderable.VertShader = "vertShader.glsl";
	asteroidRenderable.FragShader = "fragShader.glsl";
	gCoordinator.AddComponent<Renderable>(
		asteroid,
		asteroidRenderable
	);

	renderSystem->SetupShader();
}

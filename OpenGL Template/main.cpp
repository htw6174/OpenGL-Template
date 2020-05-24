// TODO: Organize ECS files into namespaces
#include "Camera.hpp"
#include "Renderable.hpp"
#include "Transform.hpp"
#include "BoxCollider.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "AsteroidSpawner.hpp"
#include "Asteroid.hpp"

#include "Coordinator.hpp"
#include "MeshUtils.h"
#include "Shapes.hpp"

#include "RenderSystem.hpp"
#include "BoxColliderSystem.hpp"
#include "PlayerSystem.hpp"
#include "BulletSystem.hpp"
#include "AsteroidSpawnerSystem.hpp"
#include "AsteroidSystem.hpp"

#include "Event.hpp"

#include "main.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

using namespace std;

Coordinator gCoordinator;
int width;
int height;
float aspect;
glm::mat4 pMat;

std::shared_ptr<RenderSystem> renderSystem;
std::shared_ptr<BoxColliderSystem> boxColliderSystem;
std::shared_ptr<PlayerSystem> playerSystem;
std::shared_ptr<BulletSystem> bulletSystem;
std::shared_ptr<AsteroidSpawnerSystem> asteroidSpawnerSystem;
std::shared_ptr<AsteroidSystem> asteroidSystem;


void window_size_callback(GLFWwindow* win, int newWidth, int newHeight) {
	aspect = (float)newWidth / (float)newHeight;
	glViewport(0, 0, newWidth, newHeight);
	renderSystem->SetProjection(glm::perspective(1.0472f, aspect, 0.1f, 1000.0f));
}

void init(GLFWwindow* window)
{
	glfwGetFramebufferSize(window, &width, &height);
	glfwSetWindowSizeCallback(window, window_size_callback);
}

void TestCollisionCallback(Entity owner, Entity other) {
	// TODO: Find another way of identifing entities now that they are an alias for a uint
	std::cout << "Entity " << owner << " collided with entity " << other << std::endl;
	//gCoordinator.DestroyEntity(owner);
	gCoordinator.DestroyEntity(other);
}

int main(void) {
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Asteroids", NULL, NULL);
	//glfwSetWindowPos(window, 200, 100);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		exit(EXIT_FAILURE);
	}
	glfwSwapInterval(1);

	init(window);
	gCoordinator.Init(window);

	gCoordinator.RegisterComponent<Camera>();
	gCoordinator.RegisterComponent<Transform>();
	gCoordinator.RegisterComponent<Renderable>();
	gCoordinator.RegisterComponent<BoxCollider>();
	gCoordinator.RegisterComponent<Player>();
	gCoordinator.RegisterComponent<Bullet>();
	gCoordinator.RegisterComponent<AsteroidSpawner>();
	gCoordinator.RegisterComponent<Asteroid>();


	renderSystem = gCoordinator.RegisterSystem<RenderSystem>();
	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Renderable>());
		signature.set(gCoordinator.GetComponentType<Transform>());
		gCoordinator.SetSystemSignature<RenderSystem>(signature);
	}

	boxColliderSystem = gCoordinator.RegisterSystem<BoxColliderSystem>();
	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Transform>());
		signature.set(gCoordinator.GetComponentType<BoxCollider>());
		gCoordinator.SetSystemSignature<BoxColliderSystem>(signature);
	}

	playerSystem = gCoordinator.RegisterSystem<PlayerSystem>();
	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Transform>());
		signature.set(gCoordinator.GetComponentType<Player>());
		gCoordinator.SetSystemSignature<PlayerSystem>(signature);
	}

	bulletSystem = gCoordinator.RegisterSystem<BulletSystem>();
	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Transform>());
		signature.set(gCoordinator.GetComponentType<BoxCollider>());
		signature.set(gCoordinator.GetComponentType<Bullet>());
		signature.set(gCoordinator.GetComponentType<Renderable>());
		gCoordinator.SetSystemSignature<BulletSystem>(signature);
	}

	asteroidSpawnerSystem = gCoordinator.RegisterSystem<AsteroidSpawnerSystem>();
	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Transform>());
		signature.set(gCoordinator.GetComponentType<AsteroidSpawner>());
		gCoordinator.SetSystemSignature<AsteroidSpawnerSystem>(signature);
	}

	asteroidSystem = gCoordinator.RegisterSystem<AsteroidSystem>();
	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Transform>());
		signature.set(gCoordinator.GetComponentType<BoxCollider>());
		signature.set(gCoordinator.GetComponentType<Asteroid>());
		gCoordinator.SetSystemSignature<AsteroidSystem>(signature);
	}

	gCoordinator.InitSystems();

	Transform cubeTransform = Transform();
	cubeTransform.SetPosition(-4.0f, 4.0f, 0.0f);

	Transform playerTransform = Transform();
	playerTransform.SetPosition(0.0f, 2.0f, 0.0f);

	Entity cube = gCoordinator.CreateEntity();
	gCoordinator.AddComponent<Transform>(
		cube,
		cubeTransform
		);

	Entity player = gCoordinator.CreateEntity();
	gCoordinator.AddComponent<Transform>(
		player,
		playerTransform
		);

	Renderable cubeRenderable = Renderable();
	cubeRenderable.VAO = MeshUtils::LoadFromArray(cubeVertexPositions, 108);
	cubeRenderable.windingOrder = GL_CW;
	//here im just setting the shader filenames, but we could probably do this better
	cubeRenderable.VertShader = "vertShader.glsl";
	cubeRenderable.FragShader = "fragShader.glsl";

	gCoordinator.AddComponent<Renderable>(
		cube,
		cubeRenderable
		);

	Renderable playerRenderable = Renderable();
	playerRenderable.VAO = MeshUtils::LoadFromArray(pyramidVertexPositions, 54);
	playerRenderable.windingOrder = GL_CCW;
	playerRenderable.VertShader = "vertShader.glsl";
	playerRenderable.FragShader = "fragShader.glsl";

	gCoordinator.AddComponent<Renderable>(
		player,
		playerRenderable
		);

	renderSystem->SetupShader();

	BoxCollider cubeCollider = BoxCollider();
	cubeCollider.boundingBox = glm::vec3(2);
	gCoordinator.AddComponent<BoxCollider>(
		cube,
		cubeCollider
		);

	boxColliderSystem->Subscribe(cube, TestCollisionCallback);

	BoxCollider playerCollider = BoxCollider();
	playerCollider.boundingBox = glm::vec3(2);
	gCoordinator.AddComponent<BoxCollider>(
		player,
		playerCollider
		);

	//boxColliderSystem->Subscribe(player, TestCollisionCallback);

#pragma region CreateAsteroidSpawner
	Entity spawner = gCoordinator.CreateEntity();
	Transform spawnerTransform = Transform();
	spawnerTransform.SetPosition(glm::vec3(0.0, -2.0, 0.0));
	gCoordinator.AddComponent<Transform>(spawner, spawnerTransform);

	AsteroidSpawner asteroidSpawner = AsteroidSpawner();
	asteroidSpawner.Period = 0.05f;
	gCoordinator.AddComponent<AsteroidSpawner>(spawner, asteroidSpawner);
	
#pragma endregion


	Player playerComponent = Player();
	//playerComponent.speed = 10.0f;

	gCoordinator.AddComponent(player, playerComponent);

	Transform* camTrans = &gCoordinator.GetComponent<Transform>(renderSystem->mCamera);
	camTrans->Translate(glm::vec3(0, 0, 15));

	int frame = 0;

	double previousTime = glfwGetTime();

	while (!glfwWindowShouldClose(window)) {
		// Calculate delta time between the previous and current frame
		double currentTime = glfwGetTime();
		float deltaTime = static_cast<float>(currentTime - previousTime);
		deltaTime = clamp(deltaTime, 0.0f, 0.1f);
		previousTime = currentTime;
		// TODO: Add universal update for systems to the system manager
		gCoordinator.UpdateSystems(deltaTime);;

		glfwSwapBuffers(window);
		glfwPollEvents();

		/*
		// RAVE
		if (frame % 4 <= 2)
		{
			gCoordinator.EnableEntity(cube);
			gCoordinator.DisableEntity(player);
		}
		else
		{
			gCoordinator.EnableEntity(player);
			gCoordinator.DisableEntity(cube);
		}
		frame++;
		*/

		float sinTime = deltaTime * sin(glfwGetTime());
		float cosTime = deltaTime * cos(glfwGetTime());
		// TODO: Find a way to handle getting a non-existant component without try-catch blocks
		try
		{
			Transform* CubeTrans = &gCoordinator.GetComponent<Transform>(cube);
			CubeTrans->Translate(glm::vec3(cosTime * 3.f, sinTime * 3.f, 0.0f));
			//CubeTrans->SetRotationEulerAngles(glm::vec3(0.0f, glm::pi<float>() / 4.0f, 0.0f));
			CubeTrans->RotateByDegrees( 100. * sinTime, glm::vec3(1.0f, 1.0f, 1.0f));
			CubeTrans->SetScale(glm::vec3(2.5f, 0.5f, 2.5f));
			//CubeTrans->RotateByDegrees(2.0f, glm::vec3(sinTime, cosTime, 0.0f));
			//std::cout << CubeTrans->GetRotation().w << std::endl;
		}
		catch (...)
		{

		}
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
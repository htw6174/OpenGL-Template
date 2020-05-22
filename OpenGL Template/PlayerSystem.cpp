#include "PlayerSystem.hpp"

extern Coordinator gCoordinator;
extern std::shared_ptr <RenderSystem> renderSystem;

bool PlayerSystem::moveForward = false;
bool PlayerSystem::rotateLeft = false;
bool PlayerSystem::rotateRight = false;
bool PlayerSystem::firing = false;

void PlayerSystem::PlayerInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_W) {
		if (action == GLFW_PRESS)
		{
			moveForward = true;
		}
		else if (action == GLFW_RELEASE)
		{
			moveForward = false;
		}
	}
	if (key == GLFW_KEY_A) {
		if (action == GLFW_PRESS)
		{
			rotateLeft = true;
		}
		else if (action == GLFW_RELEASE)
		{
			rotateLeft = false;
		}
	}
	if (key == GLFW_KEY_D) {
		if (action == GLFW_PRESS)
		{
			rotateRight = true;
		}
		else if (action == GLFW_RELEASE)
		{
			rotateRight = false;
		}
	}
	if (key == GLFW_KEY_SPACE)
	{
		if (action == GLFW_PRESS)
		{
			firing = true;
		}
		else if (action == GLFW_RELEASE)
		{
			firing = false;
		}
	}
}


void PlayerSystem::Init()
{
	glfwSetKeyCallback(gCoordinator.GetWindow(), PlayerInputCallback);
}

void PlayerSystem::Update(float deltaTime)
{
	for (auto const& entity : mEntities)
	{
		auto& transform = gCoordinator.GetComponent<Transform>(entity);
		auto& player = gCoordinator.GetComponent<Player>(entity);

		float scaledSpeed = player.speed * deltaTime;
		float scaledTurnSpeed = player.turnSpeed * deltaTime;

		if (moveForward)
		{
			transform.Translate(glm::vec3(
				scaledSpeed * cos(transform.GetRotationEulerAngles().z + glm::pi<float>() / 2.0f),
				scaledSpeed * sin(transform.GetRotationEulerAngles().z + glm::pi<float>() / 2.0f),
				0.0f)
			);
		}
		if (rotateLeft == GLFW_PRESS) {
			transform.RotateByRadians(scaledTurnSpeed, glm::vec3(0.0f, 0.0f, 1.0f));
		}
		if (rotateRight) {
			transform.RotateByRadians(-scaledTurnSpeed, glm::vec3(0.0f, 0.0f, 1.0f));
		}

		if (firing)
		{
			FireBullet(transform);
		}

	}
}

void PlayerSystem::FireBullet(Transform& transform)
{
	// TODO: Restrain the fire rate

	//std::cout << "Bullet Fired!" << std::endl;

	// make bullet Entity
	Entity bullet = gCoordinator.CreateEntity();
	
	// Setup Transform
	Transform bulletTransform = Transform();	
	// set position
	bulletTransform.SetPosition(transform.GetPosition());
	bulletTransform.SetRotationEulerAngles(transform.GetRotationEulerAngles());
	
	gCoordinator.AddComponent<Transform>(
		bullet,
		bulletTransform
	);

	// Setup Renderable
	Renderable bulletRenderable = Renderable();
	bulletRenderable.VAO = MeshUtils::LoadFromArray(pyramidVertexPositions, 54);
	bulletRenderable.windingOrder = GL_CCW;
	bulletRenderable.VertShader = "vertShader.glsl";
	bulletRenderable.FragShader = "fragShader.glsl";
	gCoordinator.AddComponent<Renderable>(
		bullet,
		bulletRenderable
	);

	renderSystem->SetupShader();

	// attach a BoxCollider
	BoxCollider bulletBoxCollider = BoxCollider();
	bulletBoxCollider.boundingBox = glm::vec3(1);
	gCoordinator.AddComponent<BoxCollider>(
		bullet,
		bulletBoxCollider
	);

	// Attach a bullet component
	Bullet bulletComponent = Bullet();
	gCoordinator.AddComponent<Bullet>(
		bullet,
		bulletComponent
	);


}
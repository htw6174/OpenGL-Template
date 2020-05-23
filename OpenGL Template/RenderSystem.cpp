#include "RenderSystem.hpp"

extern Coordinator gCoordinator;

void RenderSystem::SetProjection(glm::mat4 newProjection)
{
	gCoordinator.GetComponent<Camera>(mCamera).projectionTransform = newProjection;
}

void RenderSystem::Init()
{
	mCamera = gCoordinator.CreateEntity();

	Transform camTransform = Transform();
	camTransform.SetPosition(0.0f, 0.0f, 8.0f);

	gCoordinator.AddComponent(
		mCamera,
		camTransform
		);

	Camera cam = Camera();
	cam.projectionTransform = Camera::MakeProjectionTransform(1.0472f, 0.1f, 1000.0f, 600, 600); // 60 degress vertical FoV

	gCoordinator.AddComponent(
		mCamera,
		cam
		);

	mainRenderingProgram = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");
}

void RenderSystem::Update(float deltaTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.8, 0.6, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto const& entity : mEntities)
	{
		auto& transform = gCoordinator.GetComponent<Transform>(entity);
		auto& renderable = gCoordinator.GetComponent<Renderable>(entity);

		Camera camera = gCoordinator.GetComponent<Camera>(mCamera);
		Transform camTransform = gCoordinator.GetComponent<Transform>(mCamera);

		glUseProgram(renderable.renderingProgram);

		mvLoc = glGetUniformLocation(renderable.renderingProgram, "mv_matrix");
		projLoc = glGetUniformLocation(renderable.renderingProgram, "proj_matrix");

		pMat = camera.projectionTransform;

		vMat = glm::translate(glm::mat4(1.0f), -camTransform.GetPosition());
		glm::mat4x4 scaleMatrix = glm::scale(glm::mat4(1.0f), transform.GetScale());
		glm::mat4x4 translateMatrix = glm::translate(glm::mat4(1.0f), transform.GetPosition());
		glm::mat4x4 rotationMatrix = glm::toMat4(transform.GetRotation());
		mMat = translateMatrix;
		mMat *= rotationMatrix;
		mMat *= scaleMatrix;
		mvMat = vMat * mMat;

		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

		glEnable(GL_CULL_FACE);
		glFrontFace(renderable.windingOrder);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glBindVertexArray(renderable.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		Utils::checkOpenGLError();
	}
}

// TODO: Move this into a shader setup class
void RenderSystem::SetupShader()
{
	for (auto const& entity : mEntities)
	{
		auto& renderable = gCoordinator.GetComponent<Renderable>(entity);
		renderable.renderingProgram = mainRenderingProgram;
	}
}
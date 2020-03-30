#include "Engine.h"

//The Engine class contains a GameBase reference which it drives.

Engine::Engine(GameBase* game) {
	this->game = game; 
}

void Engine::Start() {

	renderer = new Renderer(800, 600);
	game->Start();
	renderer->Start();

	while (true) {
		Update();
		Render();
	}
}

void Engine::Update() {
	game->Update();
}

void Engine::Render() {
	game->Render();
	renderer->Render();
}

void Engine::Exit() {
	game->Exit();
	renderer->Exit();
}

//Engine Setup Functions (Called by the GameBase Implementation class)

void Engine::SetFPS(float fps) {
	FramesPerSecond = fps;
}

void Engine::SetUPS(float ups) {
	UpdatesPerSecond = ups;
}

void Engine::SetScreenSize(int Width, int Height) {
	ScreenWidth = Width;
	ScreenHeight = Height;
}
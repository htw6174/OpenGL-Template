#include "Engine.h"

//The Engine class contains a GameBase reference which it drives.

Engine::Engine(GameBase* game) {
	this->game = game; 
}

void Engine::Start() {

	this->renderer = new Renderer(600, 600);
	this->renderer->Start();
	this->game->Start();

	while (true) {
		Update();
		Render();
	}
}

void Engine::Update() {
	this->game->Update();
}

void Engine::Render() {
	this->game->Render();
	this->renderer->Render();
}

void Engine::Exit() {
	this->game->Exit();
	this->renderer->Exit();
}

//Engine Setup Functions (Called by the GameBase Implementation class)

void Engine::SetFPS(float fps) {
	this->FramesPerSecond = fps;
}

void Engine::SetUPS(float ups) {
	this->UpdatesPerSecond = ups;
}

void Engine::SetScreenSize(int Width, int Height) {
	this->ScreenWidth = Width;
	this->ScreenHeight = Height;
}
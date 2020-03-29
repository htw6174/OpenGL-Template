#pragma once

#include "GameBase.h"

class Engine {

public:
	GameBase* game;

private:
	float FramesPerSecond;
	float UpdatesPerSecond;
	int ScreenWidth, ScreenHeight;

public:
	Engine(GameBase*);
	void Start();
	void Update();
	void Render();
	void Exit();

	//Getters/Setters
	void SetFPS(float);
	void SetUPS(float);
	void SetScreenSize(int, int);
};
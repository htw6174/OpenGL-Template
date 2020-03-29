#include <iostream>

//This class serves to show a test implementation of the GameBase class
#include "TestGame.h"

void TestGame::Start() {
	GameBase::Start();
	std::cout << "TestGame Starting..." << std::endl;
}

void TestGame::Update() {
	GameBase::Update();
	std::cout << "TestGame Updating..." << std::endl;
}

void TestGame::Render() {
	GameBase::Render();
	std::cout << "TestGame Rendering..." << std::endl;
}

void TestGame::Exit() {
	GameBase::Exit();
	std::cout << "TestGame Exiting..." << std::endl;
}
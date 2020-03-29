#include "GameBase.h"
#include <iostream>

//This class serves to show a test implementation of the GameBase class

class TestGame : public GameBase {

public:
	void Start() override {
		GameBase::Start();
		std::cout << "TestGame Starting..." << std::endl;
	}

	void Update() override {
		GameBase::Update();
		std::cout << "TestGame Updating..." << std::endl;
	}

	void Render() override {
		GameBase::Render();
		std::cout << "TestGame Rendering..." << std::endl;
	}

	void Exit() override {
		GameBase::Exit();
		std::cout << "TestGame Exiting..." << std::endl;
	}
};
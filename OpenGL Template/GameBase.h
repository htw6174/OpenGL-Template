#pragma once
#include<iostream>

//All Games inherit this class

class GameBase {

public:
	virtual void Start() {
		std::cout << "GameBase Starting..." << std::endl;
	}
	virtual void Update() {
		std::cout << "GameBase Updating..." << std::endl;
	}
	virtual void Render() {
		std::cout << "GameBase Rendering..." << std::endl;
	}
	virtual void Exit() {
		std::cout << "GameBase Exiting..." << std::endl;
	}
};

#pragma once
#include<iostream>

//All Games inherit this class

class GameBase {

public:
	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

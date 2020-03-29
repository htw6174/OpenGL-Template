#pragma once
#include "GameBase.h"

class TestGame : public GameBase {
public:
	void Start() override;

	void Update() override;

	void Render() override;

	void Exit() override;
};

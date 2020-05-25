#pragma once

#include "Component.hpp"

struct Player : Component
{
private:

public:
	// Units per second
	float speed = 5.0f;
	// Radians per second
	float turnSpeed = 2.5;
	// Player firing Period
	float firePeriod = 0.2f;
	// counts up time to firePeriod
	float fireTimer = 0.0f;
};
#pragma once

#include "Component.hpp"

struct AsteroidSpawner : Component
{
public:
	// current Number
	int CurrentCount = 0;
	// Total number
	int MaxCount = 20;
	// Delay between spawns
	float Period = 1.;
};
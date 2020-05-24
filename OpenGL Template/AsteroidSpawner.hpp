#pragma once

#include "Component.hpp"

struct AsteroidSpawner : Component
{
public:
	// Total number to spawn
	int Count;
	// Delay between spawns
	float Period;
};
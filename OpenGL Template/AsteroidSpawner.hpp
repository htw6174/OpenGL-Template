#pragma once

#include "Component.hpp"

struct AsteroidSpawner : Component
{
	// Total number to spawn
	int Count;
	// Delay between spawns
	float Frequency;
};
#pragma once

#include "Component.hpp"

struct Bullet : Component
{
public:
	float speed = 30.0f;
	float lifetime = 3.0f;
};
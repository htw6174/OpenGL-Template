#pragma once

#include "Types.hpp"
#include <set>

class System
{
public:
	std::set<Entity> mEntities;
	virtual void Update(float deltaTime) = 0;
	virtual void Init() = 0;
};

#include "System.hpp"
#include "Coordinator.hpp"
#include "Transform.hpp"
#include "Asteroid.hpp"
#include <cmath>

class AsteroidSystem : public System
{
	void Init() override;
	void Update(float deltaTime) override;
};

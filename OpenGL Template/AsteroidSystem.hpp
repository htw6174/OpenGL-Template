#include "Asteroid.hpp"

#include "BoxColliderSystem.hpp"
#include "Transform.hpp"

#include "System.hpp"
#include "Coordinator.hpp"

#include <cmath>

class AsteroidSystem : public System
{
public:
	void Init() override;
	void Update(float deltaTime) override;
	void CollisionCallback(Entity owner, Entity other);

};

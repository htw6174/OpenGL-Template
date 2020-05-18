#pragma once

#include "Utils.h"

#include "Event.hpp"
#include "System.hpp"
#include "Renderable.hpp"
#include "BoxCollider.hpp"
#include "Transform.hpp"
#include "Coordinator.hpp"

#include <memory>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <cmath>
#include <map>
#include <iterator>

typedef void (*BoxCollisionEventListener) (Entity, Entity);

class BoxCollisionEvent : public Event<BoxCollisionEventListener>
{

public:
	void RaiseBoxCollisionEvent(Entity owner, Entity other);

};

class BoxColliderSystem : public System
{
public:
	bool DrawBoundingBox; //maybe for debug purposes.

	void Init() override;
	void Update() override;
	bool checkOverlap(Entity, Entity);
	void Subscribe(Entity entity, BoxCollisionEventListener callback);

private:
	std::map<Entity, BoxCollisionEvent*> BoxCollisionEventMap{};
};

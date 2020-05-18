#include "BoxColliderSystem.hpp"

extern Coordinator gCoordinator;

void BoxCollisionEvent::RaiseBoxCollisionEvent(Entity owner, Entity other) {
	for (BoxCollisionEventListener listener : Subscribers) {
		listener(owner, other);
	}
}

void BoxColliderSystem::Init() {
	//BoxCollisionEventMap = new std::map<Entity, BoxCollisionEvent*>();
	for (auto const& firstEntity : mEntities)
	{

	}
}


void BoxColliderSystem::Update() {
	std::list<std::pair<Entity, Entity>> collisions{};

	// Detect collisions
	for (auto const& owner : mEntities)
	{
		for (auto const& other : mEntities)
		{
			// do not collide with self
			if (owner == other) {
				continue;
			}

			if (checkOverlap(owner, other)) {
				// Add collision to list and resolve later
				collisions.push_back({ owner, other });
			}
		}
	}

	// Resolve collisions
	for (auto collision : collisions)
	{
		Entity owner = collision.first;
		Entity other = collision.second;

		std::map<Entity, BoxCollisionEvent*>::iterator entry = BoxCollisionEventMap.find(owner);
		// If first entity exists in event map
		if (entry != BoxCollisionEventMap.end())
		{
			// Raise event
			entry->second->RaiseBoxCollisionEvent(owner, other);
		}
	}
}

bool BoxColliderSystem::checkOverlap(Entity firstEntity, Entity secondEntity) {
	auto& firstTransform = gCoordinator.GetComponent<Transform>(firstEntity);
	BoxCollider& firstCollider = gCoordinator.GetComponent<BoxCollider>(firstEntity);

	auto& secondTransform = gCoordinator.GetComponent<Transform>(secondEntity);
	BoxCollider& secondCollider = gCoordinator.GetComponent<BoxCollider>(secondEntity);

	float firstMinX = firstTransform.GetPosition().x - (firstCollider.boundingBox.x) / 2.0f;
	float firstMaxX = firstTransform.GetPosition().x + (firstCollider.boundingBox.x) / 2.0f;
	float firstMinY = firstTransform.GetPosition().y - (firstCollider.boundingBox.y) / 2.0f;
	float firstMaxY = firstTransform.GetPosition().y + (firstCollider.boundingBox.y) / 2.0f;
	float firstMinZ = firstTransform.GetPosition().z - (firstCollider.boundingBox.z) / 2.0f;
	float firstMaxZ = firstTransform.GetPosition().z + (firstCollider.boundingBox.z) / 2.0f;

	float secondMinX = secondTransform.GetPosition().x - (secondCollider.boundingBox.x) / 2.0f;
	float secondMaxX = secondTransform.GetPosition().x + (secondCollider.boundingBox.x) / 2.0f;
	float secondMinY = secondTransform.GetPosition().y - (secondCollider.boundingBox.y) / 2.0f;
	float secondMaxY = secondTransform.GetPosition().y + (secondCollider.boundingBox.y) / 2.0f;
	float secondMinZ = secondTransform.GetPosition().z - (secondCollider.boundingBox.z) / 2.0f;
	float secondMaxZ = secondTransform.GetPosition().z + (secondCollider.boundingBox.z) / 2.0f;

	return ((firstMinX <= secondMaxX) && (firstMaxX >= secondMinX)) && 
		((firstMinY <= secondMaxY) && (firstMaxY >= secondMinY)) &&
		((firstMinZ <= secondMaxZ) && (firstMaxZ >= secondMinZ));
}

void BoxColliderSystem::Subscribe(Entity entity, BoxCollisionEventListener callback)
{
	//if entity.id NOT exists as key in BoxCollisionEventMap:
	//	add new event to map

	//add callback to entry in map

	if (gCoordinator.HasComponent<BoxCollider>(entity))
	{
		std::map<Entity, BoxCollisionEvent*>::iterator entry = BoxCollisionEventMap.find(entity);
		if (!(entry != BoxCollisionEventMap.end()))
		{
			BoxCollisionEvent* newEvent = new BoxCollisionEvent();
			newEvent->Subscribe(callback);
			//BoxCollisionEventMap[entity->id] = newEvent;
			BoxCollisionEventMap.insert(std::pair<Entity, BoxCollisionEvent*>(entity, newEvent));
		}
		else
		{
			entry->second->Subscribe(callback);
		}
	}
	else
	{
		throw std::runtime_error("Entity " + std::to_string(entity) + " can't subscribe to BoxCollision events without a BoxCollider component!");
		return;
	}
}

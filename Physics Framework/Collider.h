#pragma once
#include "Transform.h"
#include "ParticlePhysics.h"
enum class ColliderFlag {
	ColliderBase,
	SphereCollider,
	AABoxCollider,
};
class Collider
{
public:
	Collider() { transform = nullptr; particlePhysics = nullptr; m_type = ColliderFlag::ColliderBase; }
	Collider(Transform* p_transform, ParticlePhysics* p_particlePhysics) { transform = p_transform; particlePhysics = p_particlePhysics; m_type = ColliderFlag::ColliderBase; }
	virtual bool Intersects(Collider* other) { return false; }
	virtual void ResolveCollision(Collider* other) { ; }
	ColliderFlag GetType() { return m_type; }
	Transform* transform;
	ParticlePhysics* particlePhysics;
	ColliderFlag m_type;

	std::vector<Collider*> collidersToCheck;
	void AddColliderToChecklist(Collider* coll) { if(coll != this) collidersToCheck.push_back(coll); }
	virtual void Update() {
		for (auto coll : collidersToCheck) {
			ResolveCollision(coll);
		}
	}
};


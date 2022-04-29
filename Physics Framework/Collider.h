#pragma once
#include "Transform.h"
enum class ColliderFlag {
	ColliderBase,
	SphereCollider,
	AABoxCollider,
};
class Collider
{
public:
	Collider() { transform = nullptr; m_type = ColliderFlag::ColliderBase; }
	Collider(Transform* p_transform) { transform = p_transform; m_type = ColliderFlag::ColliderBase; }
	virtual bool Intersects(Collider* other) { return false; }
	ColliderFlag GetType() { return m_type; }
	Transform* transform;
	ColliderFlag m_type;
};


#pragma once
#include "Transform.h"
enum class ColliderFlag {
	ColliderBase,
	SphereCollider,
	OrientedBoxCollider,
};
class Collider
{
public:
	Collider(Transform* p_transform) { transform = p_transform; m_type = ColliderFlag::ColliderBase; }
	virtual bool Intersects(Collider* other) { return false; }
	ColliderFlag GetType() { return m_type; }

protected:
	Transform* transform;
	ColliderFlag m_type;
};


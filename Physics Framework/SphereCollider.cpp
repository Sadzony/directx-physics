#include "SphereCollider.h"
#include "AABoxCollider.h"
SphereCollider::SphereCollider(Transform* p_transform, float p_radius, ParticlePhysics* p_particlePhysics)
{
	m_type = ColliderFlag::SphereCollider;
	transform = p_transform;
	particlePhysics = p_particlePhysics;
	radius = p_radius;
}

bool SphereCollider::Intersects(Collider* other)
{
	if (other->GetType() == ColliderFlag::SphereCollider)
	{
		SphereCollider* otherSphere = dynamic_cast<SphereCollider*>(other);
		return IntersectsSphere(this, otherSphere);
	}
	else if (other->GetType() == ColliderFlag::AABoxCollider)
	{
		AABoxCollider* otherBox = dynamic_cast<AABoxCollider*>(other);
		return IntersectsBox(this, otherBox);
	}
	else {
		return false;
	}
}

bool SphereCollider::IntersectsBox(SphereCollider* thisCol, AABoxCollider* other)
{
	//box and sphere implemented in box, call on box function
	return other->IntersectsSphere(other, thisCol);
}

bool SphereCollider::IntersectsSphere(SphereCollider* thisCol, SphereCollider* other)
{
	//sphere to sphere colission#
	float distance = (thisCol->transform->GetPosition() - other->transform->GetPosition()).Length();
	float sumOfRadii = thisCol->radius + other->radius;
	if (distance < sumOfRadii) {
		return true;
	}
	else {
		return false;
	}

}

void SphereCollider::ResolveCollision(Collider* other)
{
	if (other->GetType() == ColliderFlag::SphereCollider)
	{
		SphereCollider* otherSphere = dynamic_cast<SphereCollider*>(other);
		ResolveCollisionSphere(this, otherSphere);
	}
	else if (other->GetType() == ColliderFlag::AABoxCollider)
	{
		AABoxCollider* otherBox = dynamic_cast<AABoxCollider*>(other);
		ResolveCollisionBox(this, otherBox);
	}
}

void SphereCollider::ResolveCollisionBox(SphereCollider* thisCol, AABoxCollider* other)
{
	//box and sphere implemented in box, call on box function
	other->ResolveCollisionSphere(other, thisCol);
}

void SphereCollider::ResolveCollisionSphere(SphereCollider* thisCol, SphereCollider* other)
{
	//resolve sphere to sphere collision
}

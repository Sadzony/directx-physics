#include "AABoxCollider.h"
#include "SphereCollider.h"
AABoxCollider::AABoxCollider(Transform* p_transform, Vector3D p_dimensions, ParticlePhysics* p_particlePhysics)
{
    m_type = ColliderFlag::AABoxCollider;
    transform = p_transform;
	particlePhysics = p_particlePhysics;
    dimensions = p_dimensions;
	extents = Vector3D(dimensions.x / 2, dimensions.y / 2, dimensions.z / 2);
}

bool AABoxCollider::Intersects(Collider* other)
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

bool AABoxCollider::IntersectsBox(AABoxCollider* thisCol,AABoxCollider* other)
{
	//box to box collision

	//calculate extents, positive and negative
	Vector3D thisBoxExtentsPos = thisCol->transform->GetPosition() + extents;
	Vector3D otherBoxExtentsPos = other->transform->GetPosition() + other->extents;

	Vector3D thisBoxExtentsNeg = thisCol->transform->GetPosition() - extents;
	Vector3D otherBoxExtentsNeg = other->transform->GetPosition() - other->extents;

	//check x extents
	bool checkX = (thisBoxExtentsPos.x >= otherBoxExtentsNeg.x &&  thisBoxExtentsPos.x <= otherBoxExtentsPos.x) || 
		(thisBoxExtentsNeg.x <= otherBoxExtentsPos.x && thisBoxExtentsNeg.x >= otherBoxExtentsNeg.x);
	//check y extents
	bool checkY = (thisBoxExtentsPos.y >= otherBoxExtentsNeg.y && thisBoxExtentsPos.y <= otherBoxExtentsPos.y) ||
		(thisBoxExtentsNeg.y <= otherBoxExtentsPos.y && thisBoxExtentsNeg.y >= otherBoxExtentsNeg.y);
	//check z extents
	bool checkZ = (thisBoxExtentsPos.z >= otherBoxExtentsNeg.z && thisBoxExtentsPos.z <= otherBoxExtentsPos.z) ||
		(thisBoxExtentsNeg.z <= otherBoxExtentsPos.z && thisBoxExtentsNeg.z >= otherBoxExtentsNeg.z);
	if (checkX && checkY && checkZ)
	{
		return true;
	}
	else {
		return false;
	}


}

bool AABoxCollider::IntersectsSphere(AABoxCollider* thisCol, SphereCollider* other)
{
	//box to sphere collision
	Vector3D sphereCentre = other->transform->GetPosition();
	//calculate extents, positive and negative
	Vector3D boxExtentsPos = thisCol->transform->GetPosition() + extents;
	Vector3D boxExtentsNeg = thisCol->transform->GetPosition() - extents;
	float radiusSq = other->radius * other->radius;

	float dmin = 0;
	if (sphereCentre.x < boxExtentsNeg.x) dmin += pow((sphereCentre.x - boxExtentsNeg.x), 2.0);  //check x min/max points
	else if (sphereCentre.x > boxExtentsPos.x) dmin += pow((sphereCentre.x - boxExtentsPos.x), 2.0);


	if (sphereCentre.y < boxExtentsNeg.y) dmin += pow((sphereCentre.y - boxExtentsNeg.y), 2.0); //check y min/max points
	else if (sphereCentre.y > boxExtentsPos.y) dmin += pow((sphereCentre.y - boxExtentsPos.y), 2.0);

	if (sphereCentre.z < boxExtentsNeg.z) dmin += pow((sphereCentre.z - boxExtentsNeg.z), 2.0); //check z min/max points
	else if (sphereCentre.z > boxExtentsPos.z) dmin += pow((sphereCentre.z - boxExtentsPos.z), 2.0);

	if (dmin <= radiusSq) {
		return true;
	}
	else {
		return false;
	}

}

void AABoxCollider::ResolveCollision(Collider* other)
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

void AABoxCollider::ResolveCollisionBox(AABoxCollider* thisCol, AABoxCollider* other)
{
	//box to box collision resolution
}

void AABoxCollider::ResolveCollisionSphere(AABoxCollider* thisCol, SphereCollider* other)
{
	//box to sphere collision resolution
}

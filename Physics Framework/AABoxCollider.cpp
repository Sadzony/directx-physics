#define NOMINMAX
#include "AABoxCollider.h"
#include "SphereCollider.h"
namespace extraMath {
	double clamp(double x, double upper, double lower)
	{
		return min(upper, max(x, lower));
	}
}
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

	//direction vector between the boxes
	Vector3D boxToBox = other->transform->GetPosition() - thisCol->transform->GetPosition();

	//calculate x, y, z delta (the distance between the components)
	double xDelta = std::abs(boxToBox.x);
	double yDelta = std::abs(boxToBox.y);
	double zDelta = std::abs(boxToBox.z);

	//if the distance between components is smaller than the sum of extents 
	Vector3D sum = thisCol->extents + other->extents;
	if (xDelta < sum.x &&
		yDelta < sum.y &&
		zDelta < sum.z)
	{//intersection detected

		//update position of each box to resolve the collision

		//find the penetration distance on each axis
		double xPenetration = sum.x - xDelta;
		double yPenetration = sum.y - yDelta;
		double zPenetration = sum.z - zDelta;

		//the normal needed for the collision resolution will be the lowest value of penetration distance
		Vector3D resolutionNormal;
		if (xPenetration < yPenetration && xPenetration < zPenetration) {
			resolutionNormal = Vector3D(xPenetration, 0, 0);
			thisCol->particlePhysics->AddNormalForce(resolutionNormal * -1);
			other->particlePhysics->AddNormalForce(resolutionNormal);
		}
		else if (yPenetration < xPenetration && yPenetration < zPenetration)
		{
			resolutionNormal = Vector3D(0, yPenetration, 0);
			thisCol->particlePhysics->AddNormalForce(resolutionNormal * -1);
			other->particlePhysics->AddNormalForce(resolutionNormal);

		}
		else 
		{
			resolutionNormal = Vector3D(0, 0, zPenetration);
			thisCol->particlePhysics->AddNormalForce(resolutionNormal * -1);
			other->particlePhysics->AddNormalForce(resolutionNormal);
		}
		//the value of the resolution normal is also equal to the total amount both the objects have to move to stop intersecting
		double penetrationAmount = resolutionNormal.Length();

		double thisColMoveAmount = penetrationAmount * (other->particlePhysics->GetMass() / (thisCol->particlePhysics->GetMass() + other->particlePhysics->GetMass()));
		double otherColMoveAmount = penetrationAmount * (thisCol->particlePhysics->GetMass() / (thisCol->particlePhysics->GetMass() + other->particlePhysics->GetMass()));

		//normalize the resolution normal. Scale by move amounts. This col will move negative direction, other col will move positive direction
		resolutionNormal.Normalize();
		Vector3D thisColMoveVector = -1 * resolutionNormal * thisColMoveAmount;
		Vector3D otherColMoveVector = resolutionNormal * otherColMoveAmount;

		//apply the position update to both objects transform and particle physics
		thisCol->transform->SetPosition(thisCol->transform->GetPosition() + thisColMoveVector);
		other->transform->SetPosition(other->transform->GetPosition() + otherColMoveVector);

		thisCol->particlePhysics->SetPhysicsPosition(thisCol->particlePhysics->GetPhysicsPosition() + thisColMoveVector);
		other->particlePhysics->SetPhysicsPosition(other->particlePhysics->GetPhysicsPosition() + otherColMoveVector);
	}
}

void AABoxCollider::ResolveCollisionSphere(AABoxCollider* thisCol, SphereCollider* other)
{
	//box to sphere collision resolution

	Vector3D sphereCentre = other->transform->GetPosition();
	//calculate extents, positive and negative
	Vector3D boxExtentsPos = thisCol->transform->GetPosition() + extents;
	Vector3D boxExtentsNeg = thisCol->transform->GetPosition() - extents;

	//find closest point on the box in relation to the sphere
	double closestPointX = extraMath::clamp(sphereCentre.x, boxExtentsPos.x, boxExtentsNeg.x);
	double closestPointY = extraMath::clamp(sphereCentre.y, boxExtentsPos.y, boxExtentsNeg.y);
	double closestPointZ = extraMath::clamp(sphereCentre.z, boxExtentsPos.z, boxExtentsNeg.z);

	Vector3D closestPoint = Vector3D(closestPointX, closestPointY, closestPointZ);
	
	//the collision Normal vector is the same as the vector from sphere centre to closest point on box
	Vector3D collisionNormal = closestPoint - sphereCentre;
	double distance = collisionNormal.Length();
	if (distance < other->radius) //intersection occurs if the distance to the closest point is smaller than radius
	{
		//find how much the objects are intersecting
		double penetrationDepth = other->radius - distance;

		double thisColMoveAmount = penetrationDepth * (other->particlePhysics->GetMass() / (thisCol->particlePhysics->GetMass() + other->particlePhysics->GetMass()));
		double otherColMoveAmount = penetrationDepth * (thisCol->particlePhysics->GetMass() / (thisCol->particlePhysics->GetMass() + other->particlePhysics->GetMass()));

		//the normal needed for the collision resolution will be the biggest value of collisionNormal
		Vector3D resolutionNormal;
		if (abs(collisionNormal.x) > abs(collisionNormal.y) && abs(collisionNormal.x) > abs(collisionNormal.z)) {
			resolutionNormal = Vector3D(collisionNormal.x, 0, 0);
			thisCol->particlePhysics->AddNormalForce(resolutionNormal);
			other->particlePhysics->AddNormalForce(resolutionNormal * -1);
		}
		else if (abs(collisionNormal.y) > abs(collisionNormal.x) && abs(collisionNormal.y) > abs(collisionNormal.z))
		{
			resolutionNormal = Vector3D(0, collisionNormal.y, 0);
			thisCol->particlePhysics->AddNormalForce(resolutionNormal);
			other->particlePhysics->AddNormalForce(resolutionNormal * -1);

		}
		else
		{
			resolutionNormal = Vector3D(0, 0, collisionNormal.z);
			thisCol->particlePhysics->AddNormalForce(resolutionNormal);
			other->particlePhysics->AddNormalForce(resolutionNormal * -1);
		}

		//normalize the resolution normal. Scale by move amounts. Other col will move negative direction, this col will move positive direction
		resolutionNormal.Normalize();
		Vector3D thisColMoveVector = resolutionNormal * thisColMoveAmount;
		Vector3D otherColMoveVector = -1 * resolutionNormal * otherColMoveAmount;

		//apply the position update to both objects transform and particle physics
		thisCol->transform->SetPosition(thisCol->transform->GetPosition() + thisColMoveVector);
		other->transform->SetPosition(other->transform->GetPosition() + otherColMoveVector);

		thisCol->particlePhysics->SetPhysicsPosition(thisCol->particlePhysics->GetPhysicsPosition() + thisColMoveVector);
		other->particlePhysics->SetPhysicsPosition(other->particlePhysics->GetPhysicsPosition() + otherColMoveVector);
	}
}

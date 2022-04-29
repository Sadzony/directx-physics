#include "Rigidbody.h"

Rigidbody::Rigidbody(Transform* transform, ParticlePhysics* particlePhyics, Vector3D p_centreOfMass, Vector3D p_dimensions, float p_angularDamping, bool isBall) : _transform(transform), centreOfMass(p_centreOfMass), _particlePhysics(particlePhyics), angularDamping(p_angularDamping)
{
	inertiaTensor = XMFLOAT3X3();
	dimensions = p_dimensions;
	if (!isBall) {
		inertiaTensor._11 = (1.0f / 12.0f) * particlePhyics->GetMass() * (dimensions.y, +dimensions.z);
		inertiaTensor._22 = (1.0f / 12.0f) * particlePhyics->GetMass() * (dimensions.x, +dimensions.z);
		inertiaTensor._33 = (1.0f / 12.0f) * particlePhyics->GetMass() * (dimensions.x, +dimensions.y); //inertia tensor for a cube
	}
	else {
		inertiaTensor._11 = (2.0f/5.0f) * particlePhyics->GetMass() * dimensions.x * dimensions.x;
		inertiaTensor._22 = (2.0f / 5.0f) * particlePhyics->GetMass() * dimensions.x * dimensions.x;
		inertiaTensor._33 = (2.0f / 5.0f) * particlePhyics->GetMass() * dimensions.x * dimensions.x; //inertia tensor for a sphere
	}
	angularAcceleration = Vector3D();
	angularVelocity = Vector3D();
	orientation = Quaternion();
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::Update(float deltaTime)
{
	Vector3D torque = Vector3D();
	for (ForceAndPoint force : listOfForces) { //computes every force added on that frame. The forces are pairs of powers and points
		torque += CalculateTorqueLocalPoint(force.first, force.second);
	}
	listOfForces.clear();

	CalculateAngularAcceleration(torque);
	CalculateAngularVelocity(deltaTime);
	CalculateOrientation(deltaTime);

	//torque *= angularDamping;
}

void Rigidbody::AddRotationalForce(Vector3D force, Vector3D point)
{
	listOfForces.push_back(make_pair(force, point));
}


Vector3D Rigidbody::CalculateTorque(Vector3D force, Vector3D point)
{
	point = WorldSpaceToLocalSpace(point);
	Vector3D objectPoint = point - centreOfMass;
	return objectPoint.CrossProduct(force);
}

Vector3D Rigidbody::CalculateTorqueLocalPoint(Vector3D force, Vector3D point)
{
	//calculates torque when the point is already found. Used when applying rotation directly to the object, rather than as a result of contact
	Vector3D objectPoint = point - centreOfMass;
	return objectPoint.CrossProduct(force);
}

Vector3D Rigidbody::CalculateAngularAcceleration(Vector3D torque)
{
	//acceleration = inverse of inertia tensor * torque
	XMVECTOR torqueXMVec = XMLoadFloat3(&XMFLOAT3(torque.x, torque.y, torque.z));
	XMMATRIX inverseInertiaTensor = XMMatrixInverse(nullptr, XMLoadFloat3x3(&inertiaTensor));
	XMVECTOR angularAccellerationXMVec = XMVector3Transform(torqueXMVec, inverseInertiaTensor);
	XMFLOAT3 angularAccelerationFloat3;
	XMStoreFloat3(&angularAccelerationFloat3, angularAccellerationXMVec);
	angularAcceleration = Vector3D(angularAccelerationFloat3.x, angularAccelerationFloat3.y, angularAccelerationFloat3.z);
	return angularAcceleration;


}

Vector3D Rigidbody::CalculateAngularVelocity(float deltaTime)
{
	angularVelocity = angularVelocity + (angularAcceleration * deltaTime);
	angularVelocity *=  pow(angularDamping, deltaTime); //damping^time passed - angular damping is the rotational power retained after 1 second
	return angularVelocity;
}

Quaternion Rigidbody::CalculateOrientation(float deltaTime)
{
	orientation.addScaledVector(angularVelocity, deltaTime);
	orientation.normalise();
	return orientation;
}

Vector3D Rigidbody::WorldSpaceToLocalSpace(Vector3D worldSpacePoint)
{
	//converts a point from world space to local, object space. This can be used when rotations are caused  by outside factors
	XMVECTOR pointVector = XMLoadFloat3(&XMFLOAT3(worldSpacePoint.x, worldSpacePoint.y, worldSpacePoint.z));
	XMMATRIX inverseTransformMatrix = XMMatrixInverse(nullptr, _transform->GetWorldMatrix());
	pointVector = XMVector3Transform(pointVector, inverseTransformMatrix);
	XMFLOAT3 pointVectorFloat3;
	XMStoreFloat3(&pointVectorFloat3, pointVector);
	return Vector3D(pointVectorFloat3.x, pointVectorFloat3.y, pointVectorFloat3.z);

}

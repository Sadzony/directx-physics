#include "Rigidbody.h"

Rigidbody::Rigidbody(Transform* transform, ParticlePhysics* particlePhyics, Vector3D p_centreOfMass, Vector3D dimensions, float p_angularDamping) : _transform(transform), centreOfMass(p_centreOfMass), _particlePhysics(particlePhyics), angularDamping(p_angularDamping)
{
	inertiaTensor = XMFLOAT3X3();
	inertiaTensor._11 = (1.0f / 12.0f) * particlePhyics->GetMass() * (dimensions.y, + dimensions.z);
	inertiaTensor._22 = (1.0f / 12.0f) * particlePhyics->GetMass() * (dimensions.x, + dimensions.z);
	inertiaTensor._33 = (1.0f / 12.0f) * particlePhyics->GetMass() * (dimensions.x, + dimensions.y);
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
	for (ForceAndPoint force : listOfForces) {
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
	Vector3D objectPoint = point - centreOfMass;
	return objectPoint.CrossProduct(force);
}

Vector3D Rigidbody::CalculateAngularAcceleration(Vector3D torque)
{
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
	angularVelocity *=  pow(angularDamping, deltaTime);
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
	XMVECTOR pointVector = XMLoadFloat3(&XMFLOAT3(worldSpacePoint.x, worldSpacePoint.y, worldSpacePoint.z));
	XMMATRIX inverseTransformMatrix = XMMatrixInverse(nullptr, _transform->GetWorldMatrix());
	pointVector = XMVector3Transform(pointVector, inverseTransformMatrix);
	XMFLOAT3 pointVectorFloat3;
	XMStoreFloat3(&pointVectorFloat3, pointVector);
	return Vector3D(pointVectorFloat3.x, pointVectorFloat3.y, pointVectorFloat3.z);

}

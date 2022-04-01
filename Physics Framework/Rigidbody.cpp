#include "Rigidbody.h"

Rigidbody::Rigidbody(Transform* transform, ParticlePhysics* particlePhyics, Vector3D p_centreOfMass, Vector3D dimensions, float p_angularDamping) : _transform(transform), centreOfMass(p_centreOfMass), _particlePhysics(particlePhyics), angularDamping(p_angularDamping)
{
	inertiaTensor = XMFLOAT3X3();
	inertiaTensor._11 = (1.0f / 12.0f) * particlePhyics->GetMass() * (dimensions.y, + dimensions.z);
	inertiaTensor._22 = (1.0f / 12.0f) * particlePhyics->GetMass() * (dimensions.x, + dimensions.z);
	inertiaTensor._33 = (1.0f / 12.0f) * particlePhyics->GetMass() * (dimensions.x, + dimensions.y);
}

Rigidbody::~Rigidbody()
{
	delete _transform;
	delete _particlePhysics;
}

Vector3D Rigidbody::CalculateTorque(Vector3D force, Vector3D point)
{
	Vector3D objectPoint = centreOfMass - point;
	return objectPoint.CrossProduct(force);
}

Vector3D Rigidbody::CalculateAngularAcceleration(Vector3D torque)
{
	XMFLOAT3 torqueFloat3 = XMFLOAT3(torque.x, torque.y, torque.z);
	XMVECTOR torqueXMVec = XMLoadFloat3(&torqueFloat3);
	XMMATRIX inverseInertiaTensor = XMLoadFloat3x3(&inertiaTensor);
	inverseInertiaTensor = XMMatrixInverse(new XMVECTOR(), inverseInertiaTensor);
	XMVECTOR angularAccellerationXMVec = XMVector3Transform(torqueXMVec, inverseInertiaTensor);
	XMFLOAT3 angularAccelerationFloat3;
	XMStoreFloat3(&angularAccelerationFloat3, angularAccellerationXMVec);
	angularAcceleration = Vector3D(angularAccelerationFloat3.x, angularAccelerationFloat3.y, angularAccelerationFloat3.z);
	return angularAcceleration;


}

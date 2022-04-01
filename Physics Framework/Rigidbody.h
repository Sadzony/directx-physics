#pragma once
#include "Vector3D.h"
#include "Debug.h"
#include "Transform.h"
#include "ParticlePhysics.h"
class Rigidbody
{
public:
	Transform* _transform;
	ParticlePhysics* _particlePhysics;
	
private:
	Vector3D centreOfMass;
	XMFLOAT3X3 inertiaTensor;
	float angularDamping;
	Vector3D angularAcceleration;
public:
	Rigidbody(Transform* transform, ParticlePhysics* particlePhysics, Vector3D centreOfMass, Vector3D dimensions, float p_angularDamping);
	~Rigidbody();
private:
	Vector3D CalculateTorque(Vector3D force, Vector3D point);
	Vector3D CalculateAngularAcceleration(Vector3D torque);
};


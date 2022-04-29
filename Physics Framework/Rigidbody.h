#pragma once
#include "Vector3D.h"
#include "Debug.h"
#include "Transform.h"
#include "ParticlePhysics.h"
class Rigidbody
{
	typedef std::pair<Vector3D, Vector3D> ForceAndPoint;
public:
	Transform* _transform;
	ParticlePhysics* _particlePhysics;
	
private:
	Vector3D centreOfMass;
	XMFLOAT3X3 inertiaTensor;
	float angularDamping;
	std::vector<ForceAndPoint> listOfForces;
	Vector3D angularAcceleration;
	Vector3D angularVelocity;
	Quaternion orientation;
	Vector3D dimensions;
public:
	Rigidbody(Transform* transform, ParticlePhysics* particlePhysics, Vector3D centreOfMass, Vector3D p_dimensions, float p_angularDamping, bool isBall);
	~Rigidbody();
	void Update(float deltaTime);
	void AddRotationalForce(Vector3D force, Vector3D point);

	Quaternion GetOrientation() { return orientation; }
	void SetOrientation(Quaternion p_orientation) { orientation = p_orientation; }

	Vector3D GetAngularAcceleration() { return angularAcceleration; }
	void SetAngularAcceleration(Vector3D p_acceleration) { angularAcceleration = p_acceleration; }

	Vector3D GetAngularVelocity() { return angularVelocity; }
	void SetAngularVelocity(Vector3D p_velocity) { angularVelocity = p_velocity; }

	void SetDamping(float p_damping) { angularDamping = p_damping; }

	Vector3D GetDimensions() { return dimensions; }

private:
	Vector3D CalculateTorque(Vector3D force, Vector3D point);
	Vector3D CalculateTorqueLocalPoint(Vector3D force, Vector3D point);
	Vector3D CalculateAngularAcceleration(Vector3D torque);
	Vector3D CalculateAngularVelocity(float deltaTime);
	Quaternion CalculateOrientation(float deltaTime);
	Vector3D WorldSpaceToLocalSpace(Vector3D worldSpacePoint);
};


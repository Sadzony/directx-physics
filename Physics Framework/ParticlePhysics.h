#pragma once
#include "Transform.h"
#include "Debug.h"
#include <vector>
class ParticlePhysics
{
private:
	Transform* _transform;

	float mass;
	Vector3D physicsPosition;
	Vector3D velocity;
	Vector3D acceleration;

	Vector3D netForce;
	std::vector<Vector3D> externalForces;

	bool useConstVelocity;

public:
	ParticlePhysics(Transform* transform, float pmass);
	void Update(float t);

	void SetVelocity(Vector3D pvelocity);
	Vector3D GetVelocity();

	Vector3D GetAcceleration();
	void UpdateAcceleration();

	void SetMass(float pmass);
	float GetMass();

	void AddForce(Vector3D force);
	Vector3D GetNetForce();
	void UpdateNetForce();

	void Move(float t);

	bool AllowMovement = true;
};


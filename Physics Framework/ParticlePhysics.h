#pragma once
#include "Transform.h"
#include "Debug.h"
#include <vector>
#include "AppConstants.h"
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
	void SetAcceleration(Vector3D pacceleration);
	Vector3D GetVelocity();

	Vector3D GetAcceleration();
	void UpdateAcceleration();

	void SetMass(float pmass);
	float GetMass();

	void AddWeightForce();
	void AddNormalForce();

	void AddForce(Vector3D force);
	Vector3D GetNetForce();
	void UpdateNetForce();

	void AddDrag(float dragFactor);
	Vector3D calcLaminarFlow(float dragFactor);
	Vector3D calcTurbulentFlow(float dragFactor);

	void Move(float t);

	bool AllowMovement = true;
};


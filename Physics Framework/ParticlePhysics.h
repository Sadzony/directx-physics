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

	Vector3D windVelocity;
	Vector3D dimensions;
	float radius = -1;
	float dragFactor;

public:
	ParticlePhysics(Transform* transform, float pmass, Vector3D p_dimensions, float p_dragFactor);
	ParticlePhysics(Transform* transform, float pmass, Vector3D p_dimensions, float p_radius, float p_dragFactor);
	~ParticlePhysics();
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
	void AddComplexDrag(float dragFactor, float fluidDensity, Vector3D fluidVelocity);
	Vector3D calcLaminarFlow(float dragFactor);
	Vector3D calcTurbulentFlow(float dragFactor);

	Vector3D GetWindVelocity() { return windVelocity;  }
	void SetWindVelocity(Vector3D p_windVelocity) { windVelocity = p_windVelocity; }

	Vector3D GetPhysicsPosition() { return physicsPosition; }
	void SetPhysicsPosition(Vector3D p_position) { physicsPosition = p_position; }

	void Move(float t);

	bool AllowMovement = true;
};


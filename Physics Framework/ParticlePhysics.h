#pragma once
#include "Transform.h"
enum MovementType {
	stationary,
	constant,
	accelerating
};
class ParticlePhysics
{
private:
	Transform* _transform;
	Vector3D physicsPosition;
	Vector3D velocity;
	Vector3D acceleration;
	bool toggle = false;
	MovementType moveType;
public:
	ParticlePhysics(Transform* transform, MovementType moveType);
	void Update(float t);
	void moveDirection(Vector3D direction);

	void moveConstVelocity(float t);
	void SetVelocity(Vector3D pvelocity);
	Vector3D GetVelocity();

	void moveConstAcceleration(float t);
	void SetAcceleration(Vector3D pvelocity);
	Vector3D GetAcceleration();

	void SetMovementType(MovementType newType);
	void ToggleMovement();
};


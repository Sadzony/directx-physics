#include "ParticlePhysics.h"



ParticlePhysics::ParticlePhysics(Transform* transform, MovementType pMoveType)
{
	_transform = transform;
	velocity = Vector3D(0,0,0);
	acceleration = Vector3D(0.1, 0, 0);
	moveType = pMoveType;
	physicsPosition = _transform->GetPosition();
}

void ParticlePhysics::Update(float t)
{
	if (toggle) {
		if (moveType == accelerating) {
			moveConstAcceleration(t);
		}
		else if (moveType == constant) {
			moveConstVelocity(t);
		}
	}
	_transform->SetPosition(physicsPosition);
}

void ParticlePhysics::moveDirection(Vector3D direction)
{
	physicsPosition += direction *0.02f;
}

void ParticlePhysics::moveConstVelocity(float t)
{
	physicsPosition += velocity * t;
}

void ParticlePhysics::SetVelocity(Vector3D pvelocity)
{
	velocity = pvelocity;
}

Vector3D ParticlePhysics::GetVelocity()
{
	return velocity;
}

void ParticlePhysics::moveConstAcceleration(float t)
{
	physicsPosition += velocity * t + (0.5 * acceleration * t*t);
	velocity += acceleration * t;
}

void ParticlePhysics::SetAcceleration(Vector3D pacceleration)
{
	acceleration = pacceleration;
}

Vector3D ParticlePhysics::GetAcceleration()
{
	return acceleration;
}

void ParticlePhysics::SetMovementType(MovementType newType)
{
	moveType = newType;
}

void ParticlePhysics::ToggleMovement()
{
	velocity.Zero();
	toggle = !toggle;
}

#include "ParticlePhysics.h"



ParticlePhysics::ParticlePhysics(Transform* transform, float pmass)
{
	mass = pmass;
	_transform = transform;
	velocity = Vector3D(0,0,0);
	acceleration = Vector3D(0, 0, 0);
	netForce = Vector3D(0, 0, 0);
	physicsPosition = _transform->GetPosition();
}

void ParticlePhysics::Update(float t)
{
	UpdateNetForce();
	UpdateAcceleration();
	Debug::LogString("Acceleration: ");
	Debug::LogVal((float)acceleration.x);
	Debug::LogString("\n");
	if (AllowMovement) {
		Move(t);
	}
	_transform->SetPosition(physicsPosition);
}

void ParticlePhysics::SetVelocity(Vector3D pvelocity)
{
	velocity = pvelocity;
}

Vector3D ParticlePhysics::GetVelocity()
{
	return velocity;
}

void ParticlePhysics::Move(float t)
{
	physicsPosition += velocity * t + (0.5 * acceleration * t*t);
	velocity += acceleration * t;
}

Vector3D ParticlePhysics::GetAcceleration()
{
	return acceleration;
}

void ParticlePhysics::UpdateAcceleration()
{
	acceleration = netForce / mass;
}

void ParticlePhysics::SetMass(float pmass)
{
	mass = pmass;
}

float ParticlePhysics::GetMass()
{
	return mass;
}

void ParticlePhysics::AddForce(Vector3D force)
{
	externalForces.push_back(force);
}

Vector3D ParticlePhysics::GetNetForce()
{
	return netForce;
}

void ParticlePhysics::UpdateNetForce()
{
	for each (Vector3D force in externalForces)
	{
		netForce += force;
	}
	externalForces.clear();
}

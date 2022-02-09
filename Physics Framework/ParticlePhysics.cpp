#include "ParticlePhysics.h"



ParticlePhysics::ParticlePhysics(Transform* transform)
{
	_transform = transform;
	physicsPosition = _transform->GetPosition();
}

void ParticlePhysics::Update()
{
	_transform->SetPosition(physicsPosition);
}

void ParticlePhysics::moveDirection(Vector3D direction)
{
	physicsPosition += direction *0.02f;
}

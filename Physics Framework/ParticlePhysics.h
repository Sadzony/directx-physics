#pragma once
#include "Transform.h"
class ParticlePhysics
{
private:
	Transform* _transform;
	Vector3D physicsPosition;
public:
	ParticlePhysics(Transform* transform);
	void Update();
	void moveDirection(Vector3D direction);
};


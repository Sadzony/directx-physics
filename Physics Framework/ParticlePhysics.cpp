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

ParticlePhysics::~ParticlePhysics()
{
	_transform = nullptr;
}

void ParticlePhysics::Update(float t)
{
	UpdateNetForce();
	UpdateAcceleration();
	if (AllowMovement) {
		Move(t);
	}
	_transform->SetPosition(physicsPosition);
}

void ParticlePhysics::SetVelocity(Vector3D pvelocity)
{
	velocity = pvelocity;
}

void ParticlePhysics::SetAcceleration(Vector3D pacceleration)
{
	acceleration = pacceleration;
}

Vector3D ParticlePhysics::GetVelocity()
{
	return velocity;
}

void ParticlePhysics::Move(float t)
{
	physicsPosition += velocity * t + (0.5 * acceleration * t*t);
	velocity += acceleration * t;
	if (physicsPosition.y < GROUND_Y && velocity.y < 0) {
		physicsPosition = Vector3D(physicsPosition.x, 0.5f, physicsPosition.z); //find if the object hits the ground. Currently the ground is at 0.5 all over, change this when colission detection is added
		SetVelocity(Vector3D(velocity.x, 0, velocity.z));
		SetAcceleration(Vector3D(acceleration.x, 0, acceleration.z));
	}
}

Vector3D ParticlePhysics::GetAcceleration()
{
	return acceleration;
}

void ParticlePhysics::UpdateAcceleration()
{
	acceleration = netForce / mass;
	netForce = Vector3D();
}

void ParticlePhysics::SetMass(float pmass)
{
	mass = pmass;
}

float ParticlePhysics::GetMass()
{
	return mass;
}

void ParticlePhysics::AddWeightForce()
{
	Vector3D force = Vector3D(0, mass * GRAVITY_FACTOR, 0);
	this->AddForce(force);
}

void ParticlePhysics::AddNormalForce()
{
	//find the normal force when colliding with another object
}

void ParticlePhysics::AddForce(Vector3D force)
{
	externalForces.push_back(force);
}

Vector3D ParticlePhysics::GetNetForce()
{
	return netForce;
}

//old impolementation, not in use
void ParticlePhysics::AddDrag(float dragFactor)
{
	if (velocity.Length() < LAMINAR_MAX_SPEED) {
		this->AddForce(calcLaminarFlow(dragFactor));
	}
	else {
		this->AddForce(calcTurbulentFlow(dragFactor));
	}
}
Vector3D ParticlePhysics::calcLaminarFlow(float dragFactor)
{
	return velocity * (-dragFactor);
}

Vector3D ParticlePhysics::calcTurbulentFlow(float dragFactor)
{
	float magnitude = velocity.Length();
	magnitude = dragFactor * magnitude * magnitude;
	Vector3D velNormalized = velocity.Normalized();
	return velNormalized * (-magnitude);

}
void ParticlePhysics::AddComplexDrag(float dragFactor, float fluidDensity, Vector3D fluidVelocity)
{
	//force power = 0.5 * density * relative velocity magnitude squared * area of box front face * drag coefficient
	Vector3D relativeVelocity = fluidVelocity - velocity;
	float relativeVelocityMagnitudeSq = relativeVelocity.LengthSq();
	float area = 4.0f; //this is the area of a face of cube with width and length of 2
	float forcePower;
	if (velocity.Length() < LAMINAR_MAX_SPEED) { //to calculate laminar flow, square root the length. For turbulent flow, use the squared value
		forcePower = 0.5f * fluidDensity * sqrt(relativeVelocityMagnitudeSq) * area * dragFactor;
	}
	else {
		forcePower = 0.5f * fluidDensity * relativeVelocityMagnitudeSq * area * dragFactor;
	}
	Vector3D velNormalized = relativeVelocity.Normalized();
	AddForce(velNormalized * forcePower); //add force in the opposite direction of the 
}




void ParticlePhysics::UpdateNetForce()
{
	if (_transform->GetPosition().y > GROUND_Y) {
		this->AddWeightForce();
	}
	AddComplexDrag(DRAG_FACTOR, 1.225f, Vector3D(0, 0, 0)); //add drag with no wind, and the density of air
	for each (Vector3D force in externalForces)
	{
		netForce += force;
	}
	externalForces.clear();
}


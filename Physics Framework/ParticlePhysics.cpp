#include "ParticlePhysics.h"

#define PI 3.14

ParticlePhysics::ParticlePhysics(Transform* transform, float pmass, Vector3D p_dimensions, float p_dragFactor)
{
	mass = pmass;
	_transform = transform;
	velocity = Vector3D(0,0,0);
	acceleration = Vector3D(0, 0, 0);
	netForce = Vector3D(0, 0, 0);
	windVelocity = Vector3D(0, 0, 0);
	physicsPosition = _transform->GetPosition();
	dimensions = p_dimensions;
	dragFactor = p_dragFactor;
}

ParticlePhysics::ParticlePhysics(Transform* transform, float pmass, Vector3D p_dimensions, float p_radius, float p_dragFactor)
{
	mass = pmass;
	_transform = transform;
	velocity = Vector3D(0,0,0);
	acceleration = Vector3D(0, 0, 0);
	netForce = Vector3D(0, 0, 0);
	windVelocity = Vector3D(0, 0, 0);
	physicsPosition = _transform->GetPosition();
	dimensions = p_dimensions;
	radius = p_radius;
	dragFactor = p_dragFactor;
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
	double velocityVal = velocity.Length();
	//Debug::LogString("Velocity: ");
	//Debug::LogVal((float)velocityVal);
	//Debug::LogString("\nAcceleration");                      //debug
	//double accelerationVal = acceleration.Length();
	//Debug::LogVal((float)accelerationVal);
	//Debug::LogString("\n");
	if (physicsPosition.y < GROUND_Y + dimensions.y/2 && velocity.y < 0) {
		physicsPosition = Vector3D(physicsPosition.x, dimensions.y/2, physicsPosition.z); //find if the object hits the ground. Currently the ground is at 0.0 all over, change this when colission detection is added
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
	float area;
	if (radius > 0) { //if the object is a sphere
		area = PI * radius * radius;
	}
	else { //if the object is a cube
		area = dimensions.x * dimensions.x; //this is the area of a face of cube
	}
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
	
	if (_transform->GetPosition().y > GROUND_Y + dimensions.y / 2) {
		this->AddWeightForce();
	}
	else {
		//friction
		Vector3D direction = Vector3D(velocity.x, 0, velocity.z).Normalized() * -1; //opposite direction to the velocity. ignore the y 
		double power = FRICTION_COEFFICIENT * (-1.0 * mass * GRAVITY_FACTOR); //friction power = coefficient * magnitude of normal vector. Since the normal vector is facing up, and equal to the weight force, it will be weight force * -1
		this->AddForce(direction * power);
	}
	AddComplexDrag(dragFactor, 1.225f, windVelocity); //add drag with wind velocity, and the density of air
	for each (Vector3D force in externalForces)
	{
		netForce += force;
	}
	externalForces.clear();
}


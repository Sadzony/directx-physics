#include "GameObject.h"

GameObject::GameObject(string name, ObjectType type, Transform* transform, Renderer* renderer) : _name(name), _type(type), _transform(transform), _renderer(renderer)
{
}

GameObject::GameObject(string name, ObjectType type, Transform* transform, Renderer* renderer, ParticlePhysics* particlePhysics) : _name(name), _type(type), _transform(transform), _renderer(renderer), _particlePhysics(particlePhysics)
{

}
GameObject::GameObject(string name, ObjectType type, Transform* transform, Renderer* renderer, ParticlePhysics* particlePhysics, Rigidbody* rigidbody) : _name(name), _type(type), _transform(transform), _renderer(renderer), _particlePhysics(particlePhysics), _rigidbody(rigidbody)
{

}

GameObject::GameObject(string name, ObjectType type, Transform* transform, Renderer* renderer, ParticlePhysics* particlePhysics, Rigidbody* rigidbody, Collider* collider) : _name(name), _type(type), _transform(transform), _renderer(renderer), _particlePhysics(particlePhysics), _rigidbody(rigidbody), _collider(collider)
{
}

GameObject::~GameObject()
{
	if (_type == ObjectType::PhysicsSimulated) {
		if (_rigidbody != nullptr) delete _rigidbody;
	}
	_rigidbody = nullptr;
	if (_particlePhysics != nullptr)delete _particlePhysics;
	_particlePhysics = nullptr;
	if (_renderer != nullptr)delete _renderer;
	_renderer = nullptr;
	if (_transform != nullptr)delete _transform;
	_transform = nullptr;
	if (_collider != nullptr)delete _collider;
	_collider = nullptr;
}

void GameObject::Update(float t)
{

	if (_type == ObjectType::PhysicsSimulated) {
		_rigidbody->Update(t);
		_transform->SetOrientation(_rigidbody->GetOrientation());
		_particlePhysics->Update(t);
	}
	_transform->Update();
}

void GameObject::UpdateWithCollider(float t)
{
	if (_type == ObjectType::PhysicsSimulated) {
		_rigidbody->Update(t);
		_transform->SetOrientation(_rigidbody->GetOrientation());
		_particlePhysics->Update(t);
		_collider->Update();
		_particlePhysics->UpdateToGround();
	}
	_transform->Update();
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	_renderer->Draw(pImmediateContext);
}


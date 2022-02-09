#include "GameObject.h"

GameObject::GameObject(string name, ObjectType type, Transform* transform, Renderer* renderer, ParticlePhysics* particlePhysics) : _name(name), _type(type), _transform(transform), _renderer(renderer), _particlePhysics(particlePhysics)
{
}

GameObject::~GameObject()
{
}

void GameObject::Update(float t)
{
	if (_type == ObjectType::Cube) {
		Debug::LogVal(t);
	}
	_particlePhysics->Update();
	_transform->Update();
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	_renderer->Draw(pImmediateContext);
}

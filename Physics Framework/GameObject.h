#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>
#include "Debug.h"
#include "Vector3D.h"
#include "Transform.h"
#include "ParticlePhysics.h"
#include "Renderer.h"
#include "Rigidbody.h"
#include "ColliderList.h"

using namespace DirectX;
using namespace std;


enum class ObjectType {
	Environment,
	PhysicsSimulated
};

class GameObject
{
public:
	GameObject(string name, ObjectType type, Transform* transform, Renderer* renderer);
	GameObject(string name, ObjectType type, Transform* transform, Renderer* renderer, ParticlePhysics* particlePhysics);
	GameObject(string name, ObjectType type, Transform* transform, Renderer* renderer, ParticlePhysics* particlePhysics, Rigidbody* rigidbody);
	GameObject(string name, ObjectType type, Transform* transform, Renderer* renderer, ParticlePhysics* particlePhysics, Rigidbody* rigidbody, Collider* collider);
	~GameObject();
	ObjectType GetType() const { return _type; }
	string GetName() const { return _name; }

	Transform* GetTransform() const { return _transform; }
	Renderer* GetRenderer() const { return _renderer; }
	ParticlePhysics* GetParticlePhysics() const { return _particlePhysics; }
	Rigidbody* GetRigidbody() const { return _rigidbody; }
	Collider* GetCollider() const { return _collider; }

	void Update(float t);
	void UpdateWithCollider(float t);
	void Draw(ID3D11DeviceContext* pImmediateContext);

private:
	Transform* _transform;
	Renderer* _renderer;
	ParticlePhysics* _particlePhysics;
	Rigidbody* _rigidbody;
	Collider* _collider;
	string _name;
	ObjectType _type;
};


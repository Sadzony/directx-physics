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

using namespace DirectX;
using namespace std;


enum class ObjectType {
	Environment,
	Cube
};

class GameObject
{
public:
	GameObject(string name, ObjectType type, Transform* transform, Renderer* renderer, ParticlePhysics* particlePhysics);
	GameObject(string name, ObjectType type, Transform* transform, Renderer* renderer, ParticlePhysics* particlePhysics, Rigidbody* rigidbody);
	~GameObject();
	ObjectType GetType() const { return _type; }
	string GetName() const { return _name; }

	Transform* GetTransform() const { return _transform; }
	Renderer* GetRenderer() const { return _renderer; }
	ParticlePhysics* GetParticlePhysics() const { return _particlePhysics; }
	Rigidbody* GetRigidbody() const { return _rigidbody; }

	void Update(float t);
	void Draw(ID3D11DeviceContext* pImmediateContext);

private:
	Transform* _transform;
	Renderer* _renderer;
	ParticlePhysics* _particlePhysics;
	Rigidbody* _rigidbody;
	string _name;
	ObjectType _type;
};


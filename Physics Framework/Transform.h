#pragma once
#include <directxmath.h>
#include <d3d11_1.h>
#include "Vector3D.h"
#include "Quaternion.h"

using namespace DirectX;
class Transform
{
private:
	Vector3D _position;
	Vector3D _eulerRotation;
	Quaternion _orientation;
	Vector3D _scale;
	XMFLOAT4X4 _world;
	Transform* _parent;
public:
	Transform();
	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }

	// Setters and Getters for position/rotation/scale
	void SetPosition(Vector3D position) { _position = position; }
	void SetPosition(float x, float y, float z) { _position.x = x; _position.y = y; _position.z = z; }
	Vector3D GetPosition() const { return _position; }

	void SetScale(Vector3D scale) { _scale = scale; }
	void SetScale(float x, float y, float z) { _scale.x = x; _scale.y = y; _scale.z = z; }
	Vector3D GetScale() const { return _scale; }

	void SetRotation(Vector3D EulerRotation); 
	void SetRotation(float x, float y, float z) { SetRotation(Vector3D(x, y, z)); }

	void SetOrientation(Quaternion pOrientation) { _orientation = pOrientation; }
	void SetOrientation(float r, float i, float j, float k) { _orientation.r = r; _orientation.i = i; _orientation.j = j; _orientation.k = k; }
	Quaternion GetOrientation() const { return _orientation; }
	Vector3D GetEulerRotation()const { return _eulerRotation; }

	void SetParent(Transform* parent) { _parent = parent; }

	void Update();
};


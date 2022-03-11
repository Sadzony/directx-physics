#include "Transform.h"

Transform::Transform()
{
	_parent = nullptr;
	_position = Vector3D();
	_eulerRotation = Vector3D();
	_orientation = Quaternion();
	_scale = Vector3D(1.0f, 1.0f, 1.0f);
	_world = XMFLOAT4X4();
}

void Transform::SetRotation(Vector3D pEulerRotation)
{
	_eulerRotation = pEulerRotation;
	XMVECTOR dxQuaternion = XMQuaternionRotationRollPitchYaw(_eulerRotation.x, _eulerRotation.y, _eulerRotation.z);
	XMFLOAT4 dxQuaternionFloat4;
	XMStoreFloat4(&dxQuaternionFloat4, dxQuaternion);
	_orientation = Quaternion(dxQuaternionFloat4.w, dxQuaternionFloat4.x, dxQuaternionFloat4.y, dxQuaternionFloat4.z);
}

void Transform::Update()
{
	// Calculate world matrix
	XMMATRIX scale = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	XMVECTOR dxQuaternion = XMLoadFloat4(&XMFLOAT4(_orientation.i, _orientation.j, _orientation.k, _orientation.r));
	XMMATRIX rotation = XMMatrixRotationQuaternion(dxQuaternion);
	XMMATRIX translation = XMMatrixTranslation(_position.x, _position.y, _position.z);

	XMStoreFloat4x4(&_world, scale * rotation * translation);

	if (_parent != nullptr)
	{
		XMStoreFloat4x4(&_world, this->GetWorldMatrix() * _parent->GetWorldMatrix());
	}
}

#include "GameObject.h"

GameObject::GameObject(string name, ObjectType type, Geometry geometry, Material material) : _geometry(geometry), _type(type), _material(material), _name(name)
{
	_parent = nullptr;
	_textureRV = nullptr;
	_position = Vector3D();
	_rotation = Vector3D();
	_scale = Vector3D(1.0f, 1.0f, 1.0f);
	_world = XMFLOAT4X4();
}

GameObject::~GameObject()
{
}

void GameObject::Update(float t)
{
	if (_type == ObjectType::Cube) {
		Debug::LogVal(t);
	}
	// Calculate world matrix
	XMMATRIX scale = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	XMMATRIX rotation = XMMatrixRotationX(_rotation.x) * XMMatrixRotationY(_rotation.y) * XMMatrixRotationZ(_rotation.z);
	XMMATRIX translation = XMMatrixTranslation(_position.x, _position.y, _position.z);

	XMStoreFloat4x4(&_world, scale * rotation * translation);

	if (_parent != nullptr)
	{
		XMStoreFloat4x4(&_world, this->GetWorldMatrix() * _parent->GetWorldMatrix());
	}
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	// NOTE: We are assuming that the constant buffers and all other draw setup has already taken place

	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &_geometry.vertexBuffer, &_geometry.vertexBufferStride, &_geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(_geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(_geometry.numberOfIndices, 0, 0);
}

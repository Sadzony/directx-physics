#pragma once
#include <directxmath.h>
#include <d3d11_1.h>
#include "Vector3D.h"
using namespace DirectX;
struct Geometry
{
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	int numberOfIndices;

	Vector3D centre;

	UINT vertexBufferStride;
	UINT vertexBufferOffset;
};

struct Material
{
	XMFLOAT4 diffuse;
	XMFLOAT4 ambient;
	XMFLOAT4 specular;
	float specularPower;
};
class Renderer
{
private:
	Geometry _geometry;
	Material _material;
	ID3D11ShaderResourceView* _textureRV;
public:
	Renderer(Geometry geometry, Material material);
	Geometry GetGeometryData() const { return _geometry; }

	Material GetMaterial() const { return _material; }

	void SetTextureRV(ID3D11ShaderResourceView* textureRV) { _textureRV = textureRV; }
	ID3D11ShaderResourceView* GetTextureRV() const { return _textureRV; }
	bool HasTexture() const { return _textureRV ? true : false; }


	void Draw(ID3D11DeviceContext* pImmediateContext);
};


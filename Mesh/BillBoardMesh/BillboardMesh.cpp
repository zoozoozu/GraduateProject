#include "stdafx.h"
#include "BillboardMesh.h"

CBillboardMesh::CBillboardMesh(ID3D11Device *pd3dDevice, float posX, float posY, float fWidth, float fHeight)
	:CMeshTexturedIlluminated(pd3dDevice)
{
	m_nVertices = 6;
	m_d3dPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	m_left = (float)((FRAME_BUFFER_WIDTH / 2) * -1) + (float)posX;
	m_right = m_left + (float)fWidth;
	m_top = (float)((FRAME_BUFFER_HEIGHT / 2) - (float)posY);
	m_bottom = m_top - (float)fHeight;

	float fz = 0.0f;

	m_pd3dxvPositions = new XMFLOAT3[m_nVertices];
	
	int i = 0;

	m_pd3dxvPositions[i++] = XMFLOAT3(m_left, m_top, 0.0f);
	m_pd3dxvPositions[i++] = XMFLOAT3(m_right, m_bottom, 0.0f);
	m_pd3dxvPositions[i++] = XMFLOAT3(m_left, m_bottom, 0.0f);

	m_pd3dxvPositions[i++] = XMFLOAT3(m_left, m_top, 0.0f);
	m_pd3dxvPositions[i++] = XMFLOAT3(m_right, m_top, 0.0f);
	m_pd3dxvPositions[i++] = XMFLOAT3(m_right, m_bottom, 0.0f);

	XMFLOAT2 pd3dxvTexCoords[6];
	i = 0;
	pd3dxvTexCoords[i++] = XMFLOAT2(0.0f, 0.0f);
	pd3dxvTexCoords[i++] = XMFLOAT2(1.0f, 1.0f);
	pd3dxvTexCoords[i++] = XMFLOAT2(0.0f, 1.0f);

	pd3dxvTexCoords[i++] = XMFLOAT2(0.0f, 0.0f);
	pd3dxvTexCoords[i++] = XMFLOAT2(1.0f, 0.0f);
	pd3dxvTexCoords[i++] = XMFLOAT2(1.0f, 1.0f);


	XMVECTOR pd3dxvNormals[6];
	XMFLOAT3 xmlNormals[6];
	//   for (int i = 0; i < 36; i++) pd3dxvNormals[i] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CalculateVertexNormal(pd3dxvNormals);

	for (int i = 0; i < 6; i++)
	{
		XMStoreFloat3(&xmlNormals[i], pd3dxvNormals[i]);
	}

	m_pd3dPositionBuffer = CreateBuffer(pd3dDevice, sizeof(XMFLOAT3), m_nVertices, m_pd3dxvPositions, D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_DEFAULT, 0);
	m_pd3dNormalBuffer = CreateBuffer(pd3dDevice, sizeof(XMFLOAT3), m_nVertices, xmlNormals, D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_DEFAULT, 0);
	m_pd3dTexCoordBuffer = CreateBuffer(pd3dDevice, sizeof(XMFLOAT2), m_nVertices, pd3dxvTexCoords, D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_DEFAULT, 0);

	ID3D11Buffer *pd3dBuffers[3] = { m_pd3dPositionBuffer, m_pd3dNormalBuffer, m_pd3dTexCoordBuffer };
	UINT pnBufferStrides[3] = { sizeof(XMFLOAT3), sizeof(XMFLOAT3), sizeof(XMFLOAT2) };
	UINT pnBufferOffsets[3] = { 0, 0, 0 };

	AssembleToVertexBuffer(3, pd3dBuffers, pnBufferStrides, pnBufferOffsets);
}


CBillboardMesh::~CBillboardMesh()
{
}

void CBillboardMesh::CreateRasterizerState(ID3D11Device * pd3dDevice)
{
	D3D11_RASTERIZER_DESC d3dRasterizerDesc;
	ZeroMemory(&d3dRasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	d3dRasterizerDesc.CullMode = D3D11_CULL_NONE;
	d3dRasterizerDesc.FillMode = D3D11_FILL_SOLID;
	d3dRasterizerDesc.DepthClipEnable = true;
	pd3dDevice->CreateRasterizerState(&d3dRasterizerDesc, &m_pd3dRasterizerState);
}

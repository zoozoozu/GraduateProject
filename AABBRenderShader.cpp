#include "stdafx.h"
#include "Shader/AABBRenderShader/AABBRenderShader.h"
#include "Mesh/Mesh.h"

CAABBRenderShader::CAABBRenderShader(CMesh * pMesh, int nObjects)
{
}

CAABBRenderShader::CAABBRenderShader(CMesh * pMesh)
{
}

CAABBRenderShader::CAABBRenderShader(int nObjects)
{
}

CAABBRenderShader::~CAABBRenderShader()
{
}

void CAABBRenderShader::CreateShader(ID3D11Device * pd3dDevice)
{
	D3D11_INPUT_ELEMENT_DESC d3dInputLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
		0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,
		0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	UINT nElements = ARRAYSIZE(d3dInputLayout);

	CreateVertexShaderFromFile(pd3dDevice, L"Effect.fx", "VS", "vs_5_0",
		&m_pd3dVertexShader, d3dInputLayout, nElements, &m_pd3dVertexLayout);

	CreatePixelShaderFromFile(pd3dDevice, L"Effect.fx", "PS", "ps_5_0",
		&m_pd3dPixelShader);
}

void CAABBRenderShader::UpdateConstBuffer(ID3D11DeviceContext * pd3dDeviceContext)
{
	D3D11_MAPPED_SUBRESOURCE d3dMappedResource;
	pd3dDeviceContext->Map(m_pd3dVSBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &d3dMappedResource);
	AABB *pd3dcbAABB = (AABB *)d3dMappedResource.pData;
	pd3dDeviceContext->Unmap(m_pd3dVSBuffer, 0);
	pd3dDeviceContext->VSSetConstantBuffers(VS_SLOT_AABB, 1, &m_pd3dVSBuffer);
}

void CAABBRenderShader::Render(ID3D11DeviceContext * pd3dDeviceContext, CCamera * pCamera, AABB aabb, CGameObject * pGameObject)
{
	XMFLOAT3 fSize;
	fSize.x = (aabb.m_d3dxvMaximum.x - aabb.m_d3dxvMinimum.x) * 0.5f;
	fSize.y = (aabb.m_d3dxvMaximum.y - aabb.m_d3dxvMinimum.y) * 0.5f;
	fSize.z = (aabb.m_d3dxvMaximum.z - aabb.m_d3dxvMinimum.z) * 0.5f;

	UpdateConstBuffer(pd3dDeviceContext);

	CInstancingShader::OnPrepareRender(pd3dDeviceContext);
	
	D3D11_MAPPED_SUBRESOURCE d3dMappedResource;

	int nInstances = 0;
	
	pd3dDeviceContext->Map(m_pd3dcbInstanceMatrices, 0, D3D11_MAP_WRITE_DISCARD, 0, &d3dMappedResource);
	XMMATRIX *pd3dxmtxInstances = (XMMATRIX *)d3dMappedResource.pData;

	XMMATRIX *pcbWorldMatrix = (XMMATRIX *)d3dMappedResource.pData;
	for (int j = 0; j < m_nObjects; j++)
		pcbWorldMatrix[j] = XMMatrixTranspose(XMLoadFloat4x4(&m_ppObjects[j]->m_d3dxmtxWorld));

	pd3dDeviceContext->Unmap(m_pd3dcbInstanceMatrices, 0);

	m_pMesh->RenderInstanced(pd3dDeviceContext, nInstances, 0);
}

#include "stdafx.h"
#include "Mesh/FbxMesh/FbxModelMesh/FbxModelMesh.h"
#include "Object/HeightMapTerrain/HeightMapTerrain.h"
#include "Mesh/TerrainMesh/TerrainMesh.h"
#include "Shader/InstancingShader/InstancingShader.h"
#include "Material/Texture/Texture.h"
#include "Material/Material.h"

CInstancingShader::CInstancingShader()
	:CTexturedIlluminatedShader()
{
	m_pMesh = nullptr;
	m_nObjects = 0;
	m_ppObjects = nullptr;
	m_pd3dcbInstanceMatrices = nullptr;
	m_nMatrixBufferStride = 0;
	m_nMatrixBufferOffset = 0;
}

CInstancingShader::~CInstancingShader()
{
}

void CInstancingShader::CreateShader(ID3D11Device * pd3dDevice)
{
	{
		D3D11_INPUT_ELEMENT_DESC d3dInputLayout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 2, 0 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "INSTANCEPOS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 3, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
			{ "INSTANCEPOS", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 3, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
			{ "INSTANCEPOS", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 3, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
			{ "INSTANCEPOS", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 3, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		};
		UINT nElements = ARRAYSIZE(d3dInputLayout);

		CreateVertexShaderFromFile(pd3dDevice, L"Instancing.hlsl", "VSInstancedTexturedLightingColor", "vs_5_0", &m_pd3dVertexShader, d3dInputLayout, nElements, &m_pd3dVertexLayout);
		CreatePixelShaderFromFile(pd3dDevice, L"Instancing.hlsl", "PSInstancedTexturedLightingColor", "ps_5_0", &m_pd3dPixelShader);
	}
}

void CInstancingShader::UpdateShaderVariables(ID3D11DeviceContext * pd3dDeviceContext)
{
	//��ü���� ���庯ȯ ��� �����͸� ��� ���ۿ� ����.
	D3D11_MAPPED_SUBRESOURCE d3dMappedResource;
	pd3dDeviceContext->Map(m_pd3dcbInstanceMatrices, 0, D3D11_MAP_WRITE_DISCARD, 0, &d3dMappedResource);
	XMMATRIX *pcbWorldMatrix = (XMMATRIX *)d3dMappedResource.pData;
	for (int j = 0; j < m_nObjects; j++)
		pcbWorldMatrix[j] = XMMatrixTranspose(XMLoadFloat4x4(&m_ppObjects[j]->m_d3dxmtxWorld));

	pd3dDeviceContext->Unmap(m_pd3dcbInstanceMatrices, 0);
	//pd3dDeviceContext->IASetVertexBuffers(1, 1, &m_pd3dcbInstanceMatrices, &m_nMatrixBufferStride, &m_nMatrixBufferOffset);
}

void CInstancingShader::BuildObjects(ID3D11Device *pd3dDevice, CHeightMapTerrain *pHeightMapTerrain,
	CMaterial *pMaterial, CTexture *pTexture, int k)
{
	m_pMaterial = pMaterial;
	if (pMaterial) pMaterial->AddRef();

	m_pTexture = pTexture;
	if (pTexture) pTexture->AddRef();

	m_pMesh = new CFbxModelMesh(pd3dDevice, "building-commercial_03.data", 1);
	//m_pMesh = new CCubeMesh(pd3dDevice, 30, 10, 30);
	m_nObjects = 1;
	m_ppObjects = new CGameObject*[m_nObjects];
	
	float fTerrainWidth = pHeightMapTerrain->GetWidth();
	float fTerrainLength = pHeightMapTerrain->GetLength();
	float fHeight = pHeightMapTerrain->GetHeight(fTerrainWidth, fTerrainLength);

	CRotatingObject *pBuildingModel = nullptr;
	CRotatingObject *pBoundingObject = nullptr;
	pBuildingModel = new CRotatingObject();
	pBuildingModel->SetMesh(m_pMesh);
	pBuildingModel->SetRotationAxis(XMFLOAT3(0,10,0));
	pBuildingModel->SetRotationSpeed(0);
	pBuildingModel->SetPosition(XMFLOAT3(100.0, 10, 100.0));
	m_ppObjects[0] = pBuildingModel;

	D3D11_BUFFER_DESC d3dBufferDesc;
	ZeroMemory(&d3dBufferDesc, sizeof(D3D11_BUFFER_DESC));
	d3dBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	d3dBufferDesc.ByteWidth = sizeof(XMMATRIX) * m_nObjects;
	d3dBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	d3dBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pd3dDevice->CreateBuffer(&d3dBufferDesc, NULL, &m_pd3dcbInstanceMatrices);
	//��ü �ν��Ͻ� �����͸� �޽��� �߰��Ѵ�.
	m_pMesh->AssembleToVertexBuffer(1, &m_pd3dcbInstanceMatrices, &m_nMatrixBufferStride, &m_nMatrixBufferOffset);

}

void CInstancingShader::ReleaseObjects()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) delete m_ppObjects[j];
		delete[] m_ppObjects;
	}

	if (m_pd3dcbInstanceMatrices) m_pd3dcbInstanceMatrices->Release();

}

void CInstancingShader::AnimateObjects(float fTimeElapsed)
{
}

void CInstancingShader::Render(ID3D11DeviceContext * pd3dDeviceContext, CCamera * pCamera)
{
	OnPrepareRender(pd3dDeviceContext);

	if (m_pMaterial) CIlluminatedShader::UpdateShaderVariable(pd3dDeviceContext, &m_pMaterial->m_Material);
	if (m_pTexture) m_pTexture->UpdateShaderVariable(pd3dDeviceContext);

	//��� ��ü���� �ν��Ͻ� ������(���� ��ȯ ���)�� �ν��Ͻ� ���ۿ� ����.
	UpdateShaderVariables(pd3dDeviceContext);

	//CMesh *pCubeMesh = m_ppObjects[0]->GetMesh();
	//m_pMesh = m_ppObjects[0]->GetMesh();

	m_pMesh->RenderInstanced(pd3dDeviceContext, m_nObjects, 0);
}

void CInstancingShader::SetMesh(CMesh * pMesh)
{
	if (m_pMesh) m_pMesh->Release();
	m_pMesh = pMesh;
	if (m_pMesh) m_pMesh->AddRef();
}

ID3D11Buffer * CInstancingShader::CreateInstanceBuffer(ID3D11Device * pd3dDevice, int nObjects, UINT nBufferStride, void * pBufferData)
{
	ID3D11Buffer *pd3dInstanceBuffer = NULL;
	D3D11_BUFFER_DESC d3dBufferDesc;
	ZeroMemory(&d3dBufferDesc, sizeof(D3D11_BUFFER_DESC));
	/*������ �ʱ�ȭ �����Ͱ� ������ ���� ���۷� �����Ѵ�. ��, ���߿� ������ �Ͽ� ������ ä��ų� �����Ѵ�.*/
	d3dBufferDesc.Usage = (pBufferData) ? D3D11_USAGE_DEFAULT : D3D11_USAGE_DYNAMIC;
	d3dBufferDesc.ByteWidth = nBufferStride * nObjects;
	d3dBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	d3dBufferDesc.CPUAccessFlags = (pBufferData) ? 0 : D3D11_CPU_ACCESS_WRITE;
	D3D11_SUBRESOURCE_DATA d3dBufferData;
	ZeroMemory(&d3dBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
	d3dBufferData.pSysMem = pBufferData;
	pd3dDevice->CreateBuffer(&d3dBufferDesc, (pBufferData) ? &d3dBufferData : NULL, &pd3dInstanceBuffer);
	return(pd3dInstanceBuffer);

}

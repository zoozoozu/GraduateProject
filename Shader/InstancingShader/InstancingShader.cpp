#include "stdafx.h"
#include "Mesh/FbxMesh/FbxModelMesh/FbxModelMesh.h"
#include "Object/HeightMapTerrain/HeightMapTerrain.h"
#include "Mesh/TerrainMesh/TerrainMesh.h"
#include "Shader/InstancingShader/InstancingShader.h"
#include "Material/Texture/Texture.h"
#include "Material/Material.h"

CInstancingShader::CInstancingShader(int nObjects)
	:CTexturedIlluminatedShader(nObjects)
{
	m_pd3dInstanceBuffer = NULL;
	m_pMaterial = NULL;
	m_pTexture = NULL;

	m_ppObjects = NULL;
	m_nObjects = nObjects;
	if (m_nObjects > 0)
	{
		m_ppObjects = new CGameObject*[m_nObjects];
		for (int i = 0; i < m_nObjects; i++) m_ppObjects[i] = NULL;
	}
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

void CInstancingShader::BuildObjects(ID3D11Device * pd3dDevice, CMaterial * pMaterial, CTexture * pTexture)
{
	m_pMaterial = pMaterial;
	if (pMaterial) pMaterial->AddRef();
	m_pTexture = pTexture;
	if (pTexture) pTexture->AddRef();

	m_nInstanceBufferStride = sizeof(XMMATRIX);
	m_nInstanceBufferOffset = 0;

	m_pd3dInstanceBuffer = CreateInstanceBuffer(pd3dDevice, m_nObjects, m_nInstanceBufferStride, NULL);
	m_pMesh->AssembleToVertexBuffer(1, &m_pd3dInstanceBuffer, &m_nInstanceBufferStride, &m_nInstanceBufferOffset);
}


void CInstancingShader::Render(ID3D11DeviceContext * pd3dDeviceContext, shared_ptr<CCamera> pCamera)
{
	OnPrepareRender(pd3dDeviceContext);

	if (m_pMaterial) CIlluminatedShader::UpdateShaderVariable(pd3dDeviceContext, &m_pMaterial->m_Material);
	if (m_pTexture) m_pTexture->UpdateShaderVariable(pd3dDeviceContext);

	D3D11_MAPPED_SUBRESOURCE d3dMappedResource;

	int nInstance = 0;
	pd3dDeviceContext->Map(m_pd3dInstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &d3dMappedResource);
	XMMATRIX *pcbWorldMatrix = (XMMATRIX *)d3dMappedResource.pData;
	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j])
		{
			m_ppObjects[j]->UpdateTransform(NULL);
			// 직육면체 객체가 카메라에 보일 때(직육면체 객체의 바운딩 박스가 절두체와 교차할 때) 
			// 인스턴싱 데이터를 인스턴스 버퍼로 쓴다
			if (m_ppObjects[j]->IsVisible(pCamera))
			{
				pcbWorldMatrix[nInstance++] = XMMatrixTranspose(XMLoadFloat4x4(&m_ppObjects[j]->m_xmf4x4World));
			}
		}
	}

	pd3dDeviceContext->Unmap(m_pd3dInstanceBuffer, 0);

	// 카메라에 보이는 직육면체들만 인스턴싱을 한다.
	m_pMesh->RenderInstanced(pd3dDeviceContext, nInstance, 0);
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
	/*버퍼의 초기화 데이터가 없으면 동적 버퍼로 생성한다. 즉, 나중에 매핑을 하여 내용을 채우거나 변경한다.*/
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

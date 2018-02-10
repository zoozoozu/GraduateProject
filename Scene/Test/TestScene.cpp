#include "stdafx.h"

<<<<<<< HEAD
#include "Framework\GameFramework.h"
#include "Mesh/TerrainMesh/TerrainMesh.h"

#include "Material/Texture/Texture.h"

=======
#include "Framework/GameFramework.h"
#include "Framework/IndRes/IndRes.h"

#include "Mesh/TerrainMesh/TerrainMesh.h"
#include "Material/Texture/Texture.h"
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff
#include "Mesh/AABBBoundingMesh/AABBBoundingMesh.h"

#include "Shader/SkyBoxShader/SkyBoxShader.h"
#include "Shader/TerrainShader/TerrainShader.h"
#include "Object/HeightMapTerrain/HeightMapTerrain.h"
#include "Shader/InstancingShader/InstancingShader.h"
#include "Shader/SceneShader/SceneShader.h"
#include "Shader/AABBRenderShader/AABBRenderShader.h"
<<<<<<< HEAD

#include "TestScene.h"

=======
#include "TestScene.h"


>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff
void CTestScene::CreateShaderVariables(ID3D11Device * pd3dDevice)
{
	m_pLights = new LIGHTS;
	::ZeroMemory(m_pLights, sizeof(LIGHTS));
	//���� ���� ��ü�� ���ߴ� �ֺ������� �����Ѵ�.
	m_pLights->m_d3dxcGlobalAmbient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);

	//3���� ����(�� ����, ���� ����, ���⼺ ����)�� �����Ѵ�.
	m_pLights->m_pLights[0].m_bEnable = 1.0f;
	m_pLights->m_pLights[0].m_nType = POINT_LIGHT;
	m_pLights->m_pLights[0].m_fRange = 300.0f;
	m_pLights->m_pLights[0].m_d3dxcAmbient = XMFLOAT4(0.1f, 0.0f, 0.0f, 1.0f);
	m_pLights->m_pLights[0].m_d3dxcDiffuse = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	m_pLights->m_pLights[0].m_d3dxcSpecular = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.0f);
	m_pLights->m_pLights[0].m_d3dxvPosition = XMFLOAT3(300.0f, 300.0f, 300.0f);
	m_pLights->m_pLights[0].m_d3dxvDirection = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_pLights->m_pLights[0].m_d3dxvAttenuation = XMFLOAT3(1.0f, 0.001f, 0.0001f);
	
	m_pLights->m_pLights[1].m_bEnable = 1.0f;
	m_pLights->m_pLights[1].m_nType = SPOT_LIGHT;
	m_pLights->m_pLights[1].m_fRange = 100.0f;
	m_pLights->m_pLights[1].m_d3dxcAmbient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights->m_pLights[1].m_d3dxcDiffuse = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	m_pLights->m_pLights[1].m_d3dxcSpecular = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.0f);
	m_pLights->m_pLights[1].m_d3dxvPosition = XMFLOAT3(500.0f, 300.0f, 500.0f);
	m_pLights->m_pLights[1].m_d3dxvDirection = XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_pLights->m_pLights[1].m_d3dxvAttenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights->m_pLights[1].m_fFalloff = 8.0f;
	m_pLights->m_pLights[1].m_fPhi = (float)cos(XMConvertToRadians(40.0f));
	m_pLights->m_pLights[1].m_fTheta = (float)cos(XMConvertToRadians(20.0f));
	
	m_pLights->m_pLights[2].m_bEnable = 1.0f;
	m_pLights->m_pLights[2].m_nType = DIRECTIONAL_LIGHT;
	m_pLights->m_pLights[2].m_d3dxcAmbient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	m_pLights->m_pLights[2].m_d3dxcDiffuse = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
	m_pLights->m_pLights[2].m_d3dxcSpecular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	m_pLights->m_pLights[2].m_d3dxvDirection = XMFLOAT3(0.0f, -1.0f, 0.0f);
	
	m_pLights->m_pLights[3].m_bEnable = 1.0f;
	m_pLights->m_pLights[3].m_nType = SPOT_LIGHT;
	m_pLights->m_pLights[3].m_fRange = 60.0f;
	m_pLights->m_pLights[3].m_d3dxcAmbient = XMFLOAT4(0.1f, 0.0f, 0.0f, 1.0f);
	m_pLights->m_pLights[3].m_d3dxcDiffuse = XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f);
	m_pLights->m_pLights[3].m_d3dxcSpecular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	m_pLights->m_pLights[3].m_d3dxvPosition = XMFLOAT3(500.0f, 300.0f, 500.0f);
	m_pLights->m_pLights[3].m_d3dxvDirection = XMFLOAT3(0.0f, -1.0f, 0.0f);
	m_pLights->m_pLights[3].m_d3dxvAttenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights->m_pLights[3].m_fFalloff = 20.0f;
	m_pLights->m_pLights[3].m_fPhi = (float)cos(XMConvertToRadians(40.0f));
	m_pLights->m_pLights[3].m_fTheta = (float)cos(XMConvertToRadians(15.0f));

	D3D11_BUFFER_DESC d3dBufferDesc;
	ZeroMemory(&d3dBufferDesc, sizeof(d3dBufferDesc));
	d3dBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	d3dBufferDesc.ByteWidth = sizeof(LIGHTS);
	d3dBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	d3dBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	D3D11_SUBRESOURCE_DATA d3dBufferData;
	ZeroMemory(&d3dBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
	d3dBufferData.pSysMem = m_pLights;
	pd3dDevice->CreateBuffer(&d3dBufferDesc, &d3dBufferData, &m_pd3dcbLights);

}

void CTestScene::UpdateShaderVariable(ID3D11DeviceContext * pd3dDeviceContext, LIGHTS * pLights)
{
	D3D11_MAPPED_SUBRESOURCE d3dMappedResource;
	pd3dDeviceContext->Map(m_pd3dcbLights, 0, D3D11_MAP_WRITE_DISCARD, 0, &d3dMappedResource);
	LIGHTS *pcbLight = (LIGHTS *)d3dMappedResource.pData;
	memcpy(pcbLight, pLights, sizeof(LIGHTS));
	pd3dDeviceContext->Unmap(m_pd3dcbLights, 0);
	pd3dDeviceContext->PSSetConstantBuffers(PS_SLOT_LIGHT, 1, &m_pd3dcbLights);

}

void CTestScene::ReleaseShaderVariables()
{
	if (m_pLights) delete m_pLights;
	if (m_pd3dcbLights) m_pd3dcbLights->Release();

}

CTestScene::CTestScene()
{
	m_ppShaders = nullptr;
	m_nShaders = 0;

	m_pLights = NULL;
	m_pd3dcbLights = NULL;

	m_pCamera = nullptr;
}


CTestScene::~CTestScene()
{
}

bool CTestScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return false;
}

bool CTestScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return false;
}

bool CTestScene::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return false;
}

<<<<<<< HEAD
bool CTestScene::OnCreate(wstring && tag, CGameFramework * pFramework)
{
	if (!CScene::OnCreate(std::move(tag), pFramework)) return false;

	CShader::CreateShaderVariables(m_pFramework->GetD3DDevice().Get());
	CIlluminatedShader::CreateShaderVariables(m_pFramework->GetD3DDevice().Get());

	// BuildObjects
	BuildObjects(m_pFramework->GetD3DDevice().Get());

	// Player ����
	m_pPlayerShader = new CPlayerShader();
	m_pPlayerShader->CreateShader(m_pFramework->GetD3DDevice().Get());
	m_pPlayerShader->BuildObjects(m_pFramework->GetD3DDevice().Get());
	m_pPlayer = m_pPlayerShader->GetPlayer();

	CHeightMapTerrain *pTerrain = GetTerrain();
	m_pPlayer->SetPosition(XMFLOAT3(pTerrain->GetWidth()*0.5f, pTerrain->GetPeakHeight() + 1000.0f, pTerrain->GetLength()*0.5f));

	//�÷��̾��� ��ġ�� ����� �� ������ ������ ���� �÷��̾��� ��ġ�� ������ �� �ֵ��� �����Ѵ�.
	m_pPlayer->SetPlayerUpdatedContext(pTerrain);
	//ī�޶��� ��ġ�� ����� �� ������ ������ ���� ī�޶��� ��ġ�� ������ �� �ֵ��� �����Ѵ�.
	m_pPlayer->SetCameraUpdatedContext(pTerrain);

	m_pCamera = m_pPlayer->GetCamera();
	m_pCamera->SetViewport(m_pFramework->GetD3DDeviceContext().Get(), 0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, 0.0f, 1.0f);
	m_pCamera->GenerateViewMatrix();
}

void CTestScene::BuildObjects(ID3D11Device* pd3dDevice)
=======
void CTestScene::BuildObjects(ID3D11Device * pd3dDevice)
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff
{
	//�ؽ��� ���ο� ����� ���÷� ���� ��ü�� �����Ѵ�.
	ID3D11SamplerState *pd3dSamplerState = NULL;
	D3D11_SAMPLER_DESC d3dSamplerDesc;
	ZeroMemory(&d3dSamplerDesc, sizeof(D3D11_SAMPLER_DESC));
	d3dSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	d3dSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	d3dSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	d3dSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	d3dSamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	d3dSamplerDesc.MinLOD = 0;
	d3dSamplerDesc.MaxLOD = 0;
	pd3dDevice->CreateSamplerState(&d3dSamplerDesc, &pd3dSamplerState);

	//�ؽ��� ���ҽ��� �����Ѵ�.
	ID3D11ShaderResourceView *pd3dsrvTexture = NULL;
	CTexture *pBuildingTexture = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("buildz4.jpg"), NULL, NULL, &pd3dsrvTexture, NULL);
	pBuildingTexture->SetTexture(0, pd3dsrvTexture);
	pBuildingTexture->SetSampler(0, pd3dSamplerState);
	pd3dsrvTexture->Release();
	pd3dSamplerState->Release();

	CMaterial *pNormalMaterial = new CMaterial();
	pNormalMaterial->m_Material.m_d3dxcDiffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	pNormalMaterial->m_Material.m_d3dxcAmbient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pNormalMaterial->m_Material.m_d3dxcSpecular = XMFLOAT4(1.0f, 1.0f, 1.0f, 5.0f);
	pNormalMaterial->m_Material.m_d3dxcEmissive = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
<<<<<<< HEAD

=======
	
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff
	m_nShaders = 4;
	m_ppShaders = new CShader*[m_nShaders];

	m_ppShaders[0] = new CSkyBoxShader();
	m_ppShaders[0]->CreateShader(pd3dDevice);
	m_ppShaders[0]->BuildObjects(pd3dDevice);

	m_ppShaders[1] = new CTerrainShader();
	m_ppShaders[1]->CreateShader(pd3dDevice);
	m_ppShaders[1]->BuildObjects(pd3dDevice);

	CInstancingShader *pBuildingObjectsShader = new CInstancingShader();
	pBuildingObjectsShader->CreateShader(pd3dDevice);
	pBuildingObjectsShader->BuildObjects(pd3dDevice, GetTerrain(), pNormalMaterial, pBuildingTexture, 0);
	m_ppShaders[2] = pBuildingObjectsShader;

	m_ppShaders[3] = new CSceneShader();
	m_ppShaders[3]->CreateShader(pd3dDevice);
	m_ppShaders[3]->BuildObjects(pd3dDevice);
<<<<<<< HEAD

=======
	
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff
	CreateShaderVariables(pd3dDevice);
}

void CTestScene::ReleaseObjects()
{
	ReleaseShaderVariables();

	for (int j = 0; j < m_nShaders; j++)
		m_ppShaders[j]->Release();
	if (m_ppShaders)
		delete[] m_ppShaders;
}

<<<<<<< HEAD
void CTestScene::ProcessInput(float fTimeElapsed)
{
	
=======
bool CTestScene::ProcessInput()
{
	return false;
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff
}

void CTestScene::AnimateObjects(float fTimeElapsed)
{
	if (m_pLights && m_pd3dcbLights)
	{
		//���� ī�޶��� ��ġ ���͸� ������ ��Ÿ���� ��� ���ۿ� �����Ѵ�.
		XMFLOAT3 d3dxvCameraPosition = m_pCamera->GetPosition();
		m_pLights->m_d3dxvCameraPosition = XMFLOAT4(d3dxvCameraPosition.x, d3dxvCameraPosition.y, d3dxvCameraPosition.z, 1.0f);

		//�� ������ ������ �߾��� �߽����� ȸ���ϵ��� �����Ѵ�.
		CHeightMapTerrain *pTerrain = GetTerrain();
		static XMFLOAT3 d3dxvRotated = XMFLOAT3(pTerrain->GetWidth() * 0.1f, 0.0f, 0.0f);
		XMMATRIX d3dxmtxRotate;
		d3dxmtxRotate = XMMatrixRotationRollPitchYaw(0.0f ,(float)XMConvertToRadians(30.0f*fTimeElapsed) , 0.0f);
		XMVECTOR xmvRotated = XMVector3TransformCoord(XMLoadFloat3(&d3dxvRotated), d3dxmtxRotate);
		XMStoreFloat3(&d3dxvRotated, xmvRotated);
		XMFLOAT3 d3dxvTerrainCenter = XMFLOAT3(pTerrain->GetWidth()*0.5f, pTerrain->GetPeakHeight() + 5.0f, pTerrain->GetLength()*0.5f);
		m_pLights->m_pLights[0].m_d3dxvPosition = XMFLOAT3(d3dxvTerrainCenter.x + d3dxvRotated.x, d3dxvTerrainCenter.y + d3dxvRotated.y, d3dxvTerrainCenter.z + d3dxvRotated.z);
		m_pLights->m_pLights[0].m_fRange = pTerrain->GetPeakHeight();

		/*�� ��° ������ �÷��̾ ������ �ִ� ������(���� ����)�̴�. �׷��Ƿ� �÷��̾��� ��ġ�� ������ �ٲ�� ���� �÷��̾��� ��ġ�� 
		z-�� ���� ���͸� ���� ������ ��ġ�� �������� �����Ѵ�.*/
		CPlayer *pPlayer = m_pCamera->GetPlayer();
		m_pLights->m_pLights[1].m_d3dxvPosition = pPlayer->GetPosition();
		m_pLights->m_pLights[1].m_d3dxvDirection = pPlayer->GetLookVector();

		m_pLights->m_pLights[3].m_d3dxvPosition = XMFLOAT3(pPlayer->GetPosition().x + 0.0f, pPlayer->GetPosition().y + 40.0f,
			pPlayer->GetPosition().z + 0.0f);
	}

	for (int i = 0; i < m_nShaders; i++)
	{
		m_ppShaders[i]->AnimateObjects(fTimeElapsed);
	}

}

<<<<<<< HEAD
void CTestScene::Render(ID3D11DeviceContext* pd3dDeviceContext)
{
	//CCamera *pCamera = (m_pPlayer) ? m_pPlayer->GetCamera() : NULL;

	if (m_pLights && m_pd3dcbLights) UpdateShaderVariable(pd3dDeviceContext, m_pLights);

	if (m_pPlayer) m_pPlayer->UpdateShaderVariables(pd3dDeviceContext);

=======
void CTestScene::Render(ID3D11DeviceContext *pd3dDeviceContext, ID2D1HwndRenderTarget *pd2dRenderTarget)
{
	if (m_pLights && m_pd3dcbLights) UpdateShaderVariable(pd3dDeviceContext, m_pLights);

>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff
	for (int i = 0; i < m_nShaders; i++)
	{
		m_ppShaders[i]->Render(pd3dDeviceContext, m_pCamera);
	}
<<<<<<< HEAD

	if (m_pPlayerShader) m_pPlayerShader->Render(pd3dDeviceContext, m_pCamera);
=======
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff
}

CHeightMapTerrain * CTestScene::GetTerrain()
{
	CTerrainShader *pTerrainShader = (CTerrainShader *)m_ppShaders[1];
	return(pTerrainShader->GetTerrain());
}

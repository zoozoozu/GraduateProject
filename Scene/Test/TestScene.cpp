#include "stdafx.h"

#include "Framework\GameFramework.h"
#include "Mesh/TerrainMesh/TerrainMesh.h"

#include "Material/Texture/Texture.h"

#include "Mesh/AABBBoundingMesh/AABBBoundingMesh.h"
#include "Mesh/FbxMesh/FbxModelMesh/FbxModelMesh.h"

#include "Shader/SkyBoxShader/SkyBoxShader.h"
#include "Shader/TerrainShader/TerrainShader.h"
#include "Object/HeightMapTerrain/HeightMapTerrain.h"
#include "Shader/InstancingShader/InstancingShader.h"
#include "Shader/SceneShader/SceneShader.h"

#include "TestScene.h"

void CTestScene::CreateShaderVariables(ID3D11Device * pd3dDevice)
{
	m_pLights = new LIGHTS;
	::ZeroMemory(m_pLights, sizeof(LIGHTS));
	//게임 월드 전체를 비추는 주변조명을 설정한다.
	m_pLights->m_d3dxcGlobalAmbient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);

	//3개의 조명(점 광원, 스팟 광원, 방향성 광원)을 설정한다.
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
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		////마우스 캡쳐를 하고 현재 마우스 위치를 가져온다.
		SetCapture(hWnd);
		GetCursorPos(&m_ptOldCursorPos);
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		ReleaseCapture();
		break;
	case WM_MOUSEMOVE:
		break;
	default:
		return false;
	}

	return true;
}

bool CTestScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
			/*‘F1’ 키를 누르면 1인칭 카메라, ‘F2’ 키를 누르면 스페이스-쉽 카메라로 변경한다, ‘F3’ 키를 누르면 3인칭 카메라로 변경한다.*/
		case VK_F1:
		case VK_F2:
		case VK_F3:
			if (m_pPlayer)
			{
				// 시간 수정.
				m_pPlayer->ChangeCamera(m_pFramework->GetD3DDevice().Get(), (wParam - VK_F1 + 1), 0.033f);
				m_pCamera = m_pPlayer->GetCamera();
				SetCamera(m_pCamera);
			}
			break;

		case VK_ESCAPE:
			::PostQuitMessage(0);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	
	return(true);
}

bool CTestScene::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_SIZE:
	{
		// SIZE 수정
		auto pd3dDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(wParam);
		auto pd2dDeviceContext = reinterpret_cast<ID2D1DeviceContext2*>(lParam);

		/*auto sz = m_pMasterFramework->GetClientRect();
		m_pCamera->SetViewport(pd3dDeviceContext, sz.left, sz.top, sz.right, sz.bottom, 0.0f, 1.0f);
		m_pCamera->GenerateProjectionMatrix(0.01f, 100.0f, static_cast<float>(sz.right / float(sz.bottom)), 60.0f);
		CreateRenderTargetView(pd2dDeviceContext);*/
	}
	return false;

	case WM_KEYDOWN:
	case WM_KEYUP:
		OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
		break;

	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MOUSEMOVE:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEWHEEL:
		OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
		break;

	default:
		return true;
	}

	return true;
}

bool CTestScene::OnCreate(wstring && tag, CGameFramework * pFramework)
{
	if (!CScene::OnCreate(std::move(tag), pFramework)) return false;

	CShader::CreateShaderVariables(m_pFramework->GetD3DDevice().Get());
	CIlluminatedShader::CreateShaderVariables(m_pFramework->GetD3DDevice().Get());

	// BuildObjects
	BuildObjects(m_pFramework->GetD3DDevice().Get());

	// Player 생성
	m_pPlayerShader = new CPlayerShader(1);
	m_pPlayerShader->CreateShader(m_pFramework->GetD3DDevice().Get());
	m_pPlayerShader->BuildObjects(m_pFramework->GetD3DDevice().Get());
	m_pPlayer = m_pPlayerShader->GetPlayer();

	CHeightMapTerrain *pTerrain = GetTerrain();
	m_pPlayer->SetPosition(XMFLOAT3(pTerrain->GetWidth()*0.5f, pTerrain->GetPeakHeight() + 1000.0f, pTerrain->GetLength()*0.5f));

	//플레이어의 위치가 변경될 때 지형의 정보에 따라 플레이어의 위치를 변경할 수 있도록 설정한다.
	m_pPlayer->SetPlayerUpdatedContext(pTerrain);
	//카메라의 위치가 변경될 때 지형의 정보에 따라 카메라의 위치를 변경할 수 있도록 설정한다.
	m_pPlayer->SetCameraUpdatedContext(pTerrain);

	m_pCamera = m_pPlayer->GetCamera();
	m_pCamera->SetViewport(m_pFramework->GetD3DDeviceContext().Get(), 0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, 0.0f, 1.0f);
	m_pCamera->GenerateViewMatrix();
}

void CTestScene::BuildObjects(ID3D11Device* pd3dDevice)
{
	CMesh *pBuildingMesh = new CFbxModelMesh(pd3dDevice, "building-commercial_03.data", 1.0f);
	//텍스쳐 맵핑에 사용할 샘플러 상태 객체를 생성한다.
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

	//텍스쳐 리소스를 생성한다.
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

	m_nShaders = 3;
	m_ppShaders = new CShader*[m_nShaders];

	m_ppShaders[0] = new CSkyBoxShader(1);
	m_ppShaders[0]->CreateShader(pd3dDevice);
	m_ppShaders[0]->BuildObjects(pd3dDevice);

	m_ppShaders[1] = new CTerrainShader(1);
	m_ppShaders[1]->CreateShader(pd3dDevice);
	m_ppShaders[1]->BuildObjects(pd3dDevice);

	m_ppShaders[2] = new CSceneShader(1);
	m_ppShaders[2]->CreateShader(pd3dDevice);
	m_ppShaders[2]->BuildObjects(pd3dDevice);

	m_nInstancingShaders = 1;
	m_ppInstancingShaders = new CInstancingShader*[m_nInstancingShaders];

	m_ppInstancingShaders[0] = new CInstancingShader(1);
	m_ppInstancingShaders[0]->SetMesh(pBuildingMesh);
	m_ppInstancingShaders[0]->CreateShader(pd3dDevice);
	m_ppInstancingShaders[0]->BuildObjects(pd3dDevice, pNormalMaterial, pBuildingTexture);

	CGameObject *pBuildingObject = new CGameObject(1);
	pBuildingObject->SetPosition(XMFLOAT3(2500.f, 0.f, 2500.f));
	pBuildingObject->Rotate(0.0f, -45.0f, 0.f);
	m_ppInstancingShaders[0]->AddObject(pBuildingObject);
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

void CTestScene::ProcessInput(float fTimeElapsed)
{
	static UCHAR pKeyBuffer[256];
	DWORD dwDirection = 0;
	// 키보드의 상태 정보를 반환한다.
	// 화살표 키를 누르면 플레이어를 오른쪽/왼쪽(로컬 x-축), 앞/뒤(로컬 z-축)로 이동한다.
	// 'Page Up'과 'Page Down'키를 누르면 플레이어를 위/아래(로컬 y-축)로 이동한다.
	if (GetKeyboardState(pKeyBuffer))
	{
		if (pKeyBuffer['W'] & 0xF0) dwDirection |= DIR_FORWARD;
		if (pKeyBuffer['S'] & 0xF0) dwDirection |= DIR_BACKWARD;
		if (pKeyBuffer['A'] & 0xF0) dwDirection |= DIR_LEFT;
		if (pKeyBuffer['D'] & 0xF0) dwDirection |= DIR_RIGHT;
		if (pKeyBuffer[VK_PRIOR] & 0xF0) dwDirection |= DIR_UP;
		if (pKeyBuffer[VK_NEXT] & 0xF0) dwDirection |= DIR_DOWN;
	}
	float cxDelta = 0.0f, cyDelta = 0.0f;
	POINT ptCursorPos;
	// 마우스를 캡쳐했으면 마우스가 얼마만큼 이동하였는 가를 계산한다.
	// 마우스 왼쪽 또는 오른쪽 버튼이 눌러질 때의 메시지를 처리할 때 마우스를 캡쳐하였다.
	// 그러므로 마우스가 캡쳐된 것은 마우스 버튼이 눌려진 상태를 의미한다.
	// 마우스를 좌우 또는 상하로 움직이면 플레이어를 x-축 또는 y-축으로 회전한다.
	if (GetCapture() == m_hWnd)
	{
		// 마우스 커서를 화면에서 없앤다.(보이지 않게 한다.)
		SetCursor(NULL);
		// 현재 마우스 커서의 위치를 가져온다.
		GetCursorPos(&ptCursorPos);
		// 마우스 버튼이 눌린 채로 이전 위치에서 현재 마우스 커서의 위치까지 움직인 양을 구한다.
		cxDelta = (float)(ptCursorPos.x - m_ptOldCursorPos.x) / 3.0f;
		cyDelta = (float)(ptCursorPos.y - m_ptOldCursorPos.y) / 3.0f;
		SetCursorPos(m_ptOldCursorPos.x, m_ptOldCursorPos.y);
	}

	// 플레이어를 이동하거나(dwDirection) 회전한다(cxDelta 또는 cyDelta).
	if ((dwDirection != 0) || (cxDelta != 0.0f) || (cyDelta != 0.0f))
	{
		if (cxDelta || cyDelta)
		{
			// cxDelta는 y-축의 회전을 나타내고 cyDelta는 x축의 회전을 나타낸다.
			// 오른쪽 마우스 버튼이 눌려진 경우 cxDelta는 z축의 회전을 나타낸다.
			if (pKeyBuffer[VK_RBUTTON] & 0xF0)
				m_pPlayer->Rotate(cyDelta, 0.0f, -cxDelta);
			else
				m_pPlayer->Rotate(cyDelta, cxDelta, 0.0f);
		}
		// 플레이어를 dwDirection 방향으로 이동한다(실제로는 속도 벡터를 변경한다.)
		// 이동 거리는 시간에 비례하도록 한다.
		// 플레이어의 이동 속력은(50/초)로 가정한다.
		// 만약 플레이어의 이동 속력이 있다면 그 값을 사용한다.
		if (dwDirection)
			m_pPlayer->Move(dwDirection, 50.0f * fTimeElapsed, true);
	}
	// 플레이어를 실제로 이동하고 카메라를 갱신한다.
	// 중력과 마찰력의 영향을 속도 벡터에 적용한다.
	m_pPlayer->Update(fTimeElapsed);
}


void CTestScene::AnimateObjects(float fTimeElapsed)
{
	if (m_pLights && m_pd3dcbLights)
	{
		//현재 카메라의 위치 벡터를 조명을 나타내는 상수 버퍼에 설정한다.
		XMFLOAT3 d3dxvCameraPosition = m_pCamera->GetPosition();
		m_pLights->m_d3dxvCameraPosition = XMFLOAT4(d3dxvCameraPosition.x, d3dxvCameraPosition.y, d3dxvCameraPosition.z, 1.0f);

		//점 조명이 지형의 중앙을 중심으로 회전하도록 설정한다.
		CHeightMapTerrain *pTerrain = GetTerrain();
		static XMFLOAT3 d3dxvRotated = XMFLOAT3(pTerrain->GetWidth() * 0.1f, 0.0f, 0.0f);
		XMMATRIX d3dxmtxRotate;
		d3dxmtxRotate = XMMatrixRotationRollPitchYaw(0.0f ,(float)XMConvertToRadians(30.0f*fTimeElapsed) , 0.0f);
		XMVECTOR xmvRotated = XMVector3TransformCoord(XMLoadFloat3(&d3dxvRotated), d3dxmtxRotate);
		XMStoreFloat3(&d3dxvRotated, xmvRotated);
		XMFLOAT3 d3dxvTerrainCenter = XMFLOAT3(pTerrain->GetWidth()*0.5f, pTerrain->GetPeakHeight() + 5.0f, pTerrain->GetLength()*0.5f);
		m_pLights->m_pLights[0].m_d3dxvPosition = XMFLOAT3(d3dxvTerrainCenter.x + d3dxvRotated.x, d3dxvTerrainCenter.y + d3dxvRotated.y, d3dxvTerrainCenter.z + d3dxvRotated.z);
		m_pLights->m_pLights[0].m_fRange = pTerrain->GetPeakHeight();

		/*두 번째 조명은 플레이어가 가지고 있는 손전등(스팟 조명)이다. 그러므로 플레이어의 위치와 방향이 바뀌면 현재 플레이어의 위치와 
		z-축 방향 벡터를 스팟 조명의 위치와 방향으로 설정한다.*/
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

	for (int i = 0; i < m_nInstancingShaders; i++)
	{
		m_ppInstancingShaders[i]->AnimateObjects(fTimeElapsed);
	}

}

void CTestScene::Render(ID3D11DeviceContext* pd3dDeviceContext)
{
	//CCamera *pCamera = (m_pPlayer) ? m_pPlayer->GetCamera() : NULL;

	if (m_pLights && m_pd3dcbLights) UpdateShaderVariable(pd3dDeviceContext, m_pLights);

	if (m_pPlayer) m_pPlayer->UpdateShaderVariables(pd3dDeviceContext);

	for (int i = 0; i < m_nShaders; i++)
	{
		m_ppShaders[i]->Render(pd3dDeviceContext, m_pCamera);
	}

	for (int i = 0; i < m_nInstancingShaders; i++)
	{
		m_ppInstancingShaders[i]->Render(pd3dDeviceContext, m_pCamera);
	}

	if (m_pPlayerShader) m_pPlayerShader->Render(pd3dDeviceContext, m_pCamera);
}

CHeightMapTerrain * CTestScene::GetTerrain()
{
	CTerrainShader *pTerrainShader = (CTerrainShader *)m_ppShaders[1];
	return(pTerrainShader->GetTerrain());
}

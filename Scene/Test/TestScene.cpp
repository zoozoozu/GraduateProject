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
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		////���콺 ĸ�ĸ� �ϰ� ���� ���콺 ��ġ�� �����´�.
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
			/*��F1�� Ű�� ������ 1��Ī ī�޶�, ��F2�� Ű�� ������ �����̽�-�� ī�޶�� �����Ѵ�, ��F3�� Ű�� ������ 3��Ī ī�޶�� �����Ѵ�.*/
		case VK_F1:
		case VK_F2:
		case VK_F3:
			if (m_pPlayer)
			{
				// �ð� ����.
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
		// SIZE ����
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

	// Player ����
	m_pPlayerShader = new CPlayerShader(1);
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
{
	//�ؽ��� ����ftvbygunhimjkp.l/;'�� ����� ���÷� ���� ��ü�� �����Ѵ�.
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

	ID3D11SamplerState *pd3dUISamplerState = NULL;
	ZeroMemory(&d3dSamplerDesc, sizeof(D3D11_SAMPLER_DESC));
	d3dSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	d3dSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	d3dSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	d3dSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	d3dSamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	d3dSamplerDesc.MinLOD = 0;
	d3dSamplerDesc.MaxLOD = 0;
	pd3dDevice->CreateSamplerState(&d3dSamplerDesc, &pd3dUISamplerState);

	//�ؽ��� ���ҽ��� �����Ѵ�.
	ID3D11ShaderResourceView *pd3dsrvTexture = NULL;

	// SoldierTexture
	CTexture *pSoldierTexture = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("../Data/Animation/eunbee_idle.png"), NULL, NULL, &pd3dsrvTexture, NULL);
	pSoldierTexture->SetTexture(0, pd3dsrvTexture);
	pSoldierTexture->SetSampler(0, pd3dSamplerState);
	pd3dsrvTexture->Release();

	// NinjaTexture
	pd3dsrvTexture = NULL;
	CTexture *pNinjaTexture = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("../Data/Animation/Ninja_diffuse.png"), NULL, NULL, &pd3dsrvTexture, NULL);
	pNinjaTexture->SetTexture(0, pd3dsrvTexture);
	pNinjaTexture->SetSampler(0, pd3dSamplerState);
	pd3dsrvTexture->Release();

	pd3dsrvTexture = NULL;
	CTexture *pContainerTexture = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("../Data/Texture/containers_diffuse.png"), NULL, NULL, &pd3dsrvTexture, NULL);
	pContainerTexture->SetTexture(0, pd3dsrvTexture);
	pContainerTexture->SetSampler(0, pd3dSamplerState);

	pd3dsrvTexture = NULL;
	CTexture *pContainerTexture1 = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("../Data/Texture/containers_diffuse2.png"), NULL, NULL, &pd3dsrvTexture, NULL);
	pContainerTexture1->SetTexture(0, pd3dsrvTexture);
	pContainerTexture1->SetSampler(0, pd3dSamplerState);

	pd3dsrvTexture = NULL;
	CTexture *pBarrierTexture = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("../Data/Texture/Barrier_01.png"), NULL, NULL, &pd3dsrvTexture, NULL);
	pBarrierTexture->SetTexture(0, pd3dsrvTexture);
	pBarrierTexture->SetSampler(0, pd3dSamplerState);

	pd3dsrvTexture = NULL;
	CTexture *pWindowTexture_001 = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("../Data/Texture/Windows_001[9].png"), NULL, NULL, &pd3dsrvTexture, NULL);
	pWindowTexture_001->SetTexture(0, pd3dsrvTexture);
	pWindowTexture_001->SetSampler(0, pd3dSamplerState);

	pd3dsrvTexture = NULL;
	CTexture *pWindowTexture_003 = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("../Data/Texture/Windows_001[10].png"), NULL, NULL, &pd3dsrvTexture, NULL);
	pWindowTexture_003->SetTexture(0, pd3dsrvTexture);
	pWindowTexture_003->SetSampler(0, pd3dSamplerState);

	pd3dsrvTexture = NULL;
	CTexture *pBuilding1Texture = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("../Data/Texture/t_002_b001-2_style2_basecolor.png"), NULL, NULL, &pd3dsrvTexture, NULL);
	pBuilding1Texture->SetTexture(0, pd3dsrvTexture);
	pBuilding1Texture->SetSampler(0, pd3dSamplerState);

	pd3dsrvTexture = NULL;
	CTexture *pBuilding2Texture = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("../Data/Texture/t_002_b002-2_style2_basecolor.png"), NULL, NULL, &pd3dsrvTexture, NULL);
	pBuilding2Texture->SetTexture(0, pd3dsrvTexture);
	pBuilding2Texture->SetSampler(0, pd3dSamplerState);

	pd3dsrvTexture = NULL;
	CTexture *pBuilding3Texture = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("../Data/Texture/t_002_b003_style2_basecolor.png"), NULL, NULL, &pd3dsrvTexture, NULL);
	pBuilding3Texture->SetTexture(0, pd3dsrvTexture);
	pBuilding3Texture->SetSampler(0, pd3dSamplerState);

	pd3dsrvTexture = NULL;
	CTexture *pOther1Texture = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("../Data/Texture/chimney_Albedo.png"), NULL, NULL, &pd3dsrvTexture, NULL);
	pOther1Texture->SetTexture(0, pd3dsrvTexture);
	pOther1Texture->SetSampler(0, pd3dSamplerState);

	// ������ �����ϱ�.
	pd3dsrvTexture = NULL;
	CTexture *pDoorTexture = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("../Data/Texture/chimney_Albedo.png"), NULL, NULL, &pd3dsrvTexture, NULL);
	pDoorTexture->SetTexture(0, pd3dsrvTexture);
	pDoorTexture->SetSampler(0, pd3dSamplerState);

	pd3dsrvTexture = nullptr;
	CTexture *pGunTexture = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("../Data/Texture/rifle_diff.jpg"), NULL, NULL, &pd3dsrvTexture, NULL);
	pGunTexture->SetTexture(0, pd3dsrvTexture);
	pGunTexture->SetSampler(0, pd3dUISamplerState);

	pd3dsrvTexture = nullptr;
	CTexture *pUICrosshairTexture = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("../Data/Target/gun-pointer (1).png"), NULL, NULL, &pd3dsrvTexture, NULL);
	pUICrosshairTexture->SetTexture(0, pd3dsrvTexture);
	pUICrosshairTexture->SetSampler(0, pd3dUISamplerState);

	pd3dsrvTexture = nullptr;
	CTexture *pUICharacter1Texture = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("../Data/Texture/UI_Character_1_����1.png"), NULL, NULL, &pd3dsrvTexture, NULL);
	pUICharacter1Texture->SetTexture(0, pd3dsrvTexture);
	pUICharacter1Texture->SetSampler(0, pd3dUISamplerState);

	pd3dsrvTexture = nullptr;
	CTexture *pUIHPTexture = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("../Data/Texture/INGAMEUI_HPGauge_Red.png"), NULL, NULL, &pd3dsrvTexture, NULL);
	pUIHPTexture->SetTexture(0, pd3dsrvTexture);
	pUIHPTexture->SetSampler(0, pd3dUISamplerState);

	pd3dsrvTexture = nullptr;
	CTexture *pIngameTextTexture = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("../Data/Texture/Ingame_Texture2.png"), NULL, NULL, &pd3dsrvTexture, NULL);
	pIngameTextTexture->SetTexture(0, pd3dsrvTexture);
	pIngameTextTexture->SetSampler(0, pd3dUISamplerState);
	
	//0812
	/*pd3dsrvTexture = NULL;
	pRedTeamRespawnTex = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("Data/Texture/REDTEAMZONE.png"), NULL, NULL, &pd3dsrvTexture, NULL);
	pRedTeamRespawnTex->SetTexture(0, pd3dsrvTexture);
	pRedTeamRespawnTex->SetSampler(0, pd3dUISamplerState);

	pd3dsrvTexture = NULL;
	pBlueTeamRespawnTex = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("Data/Texture/BLUETEAMZONE.png"), NULL, NULL, &pd3dsrvTexture, NULL);
	pBlueTeamRespawnTex->SetTexture(0, pd3dsrvTexture);
	pBlueTeamRespawnTex->SetSampler(0, pd3dUISamplerState);

	CTexture *pHPcharge = new CTexture(1, 1, 0, 0);
	D3DX11CreateShaderResourceViewFromFile(pd3dDevice, _T("Data/Texture/hp����.png"), NULL, NULL, &pd3dsrvTexture, NULL);
	pHPcharge->SetTexture(0, pd3dsrvTexture);
	pHPcharge->SetSampler(0, pd3dUISamplerState);
*/
	pd3dsrvTexture->Release();
	pd3dSamplerState->Release();

	CMaterial *pNormalMaterial = new CMaterial();
	pNormalMaterial->m_Material.m_d3dxcDiffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	pNormalMaterial->m_Material.m_d3dxcAmbient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pNormalMaterial->m_Material.m_d3dxcSpecular = XMFLOAT4(1.0f, 1.0f, 1.0f, 5.0f);
	pNormalMaterial->m_Material.m_d3dxcEmissive = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

	// Mesh
	// Container
	CMesh *pContainer1Mesh = new CFbxModelMesh(pd3dDevice, "../Data/container/container_1.data", 1.0f);
	CMesh *pContainer2Mesh = new CFbxModelMesh(pd3dDevice, "../Data/container/container_2.data", 1.0f);
	CMesh *pContainer3Mesh = new CFbxModelMesh(pd3dDevice, "../Data/container/container_3.data", 1.0f);
	CMesh *pContainer4Mesh = new CFbxModelMesh(pd3dDevice, "../Data/container/container_4.data", 1.0f);

	// NewTexture Container
	CMesh *pContainer5Mesh = new CFbxModelMesh(pd3dDevice, "../Data/container/container_1.data", 1.0f);
	CMesh *pContainer6Mesh = new CFbxModelMesh(pd3dDevice, "../Data/container/container_2.data", 1.0f);
	CMesh *pContainer7Mesh = new CFbxModelMesh(pd3dDevice, "../Data/container/container_3.data", 1.0f);
	CMesh *pContainer8Mesh = new CFbxModelMesh(pd3dDevice, "../Data/container/container_4.data", 1.0f);

	// Open Container1
	CMesh *pOpenContainer1_Mesh1 = new CFbxModelMesh(pd3dDevice, "../Data/container/container_1_open_Mesh1.data", 1.0f);

	// Open Container2
	CMesh *pOpenContainer2_Mesh1 = new CFbxModelMesh(pd3dDevice, "../Data/container/container_2_open_Mesh1.data", 1.0f);

	// Barrier
	CMesh *pBarrier1Mesh = new CFbxModelMesh(pd3dDevice, "../Data/container/barrier_small.data", 1.0f);
	CMesh *pBarrier2Mesh = new CFbxModelMesh(pd3dDevice, "../Data/container/barrier_small.data", 1.0f);

	// Building
	CMesh *pWindow1Mesh = new CFbxModelMesh(pd3dDevice, "../Data/BuildingObject/window_001.data", 1.0f);
	CMesh *pWindow3Mesh = new CFbxModelMesh(pd3dDevice, "../Data/BuildingObject/window_003.data", 1.0f);

	CMesh *pBuilding1Mesh = new CFbxModelMesh(pd3dDevice, "../Data/BuildingObject/t_002_b001-2.data", 1.0f);
	CMesh *pBuilding2Mesh = new CFbxModelMesh(pd3dDevice, "../Data/BuildingObject/t_002_b002-2.data", 1.0f);
	CMesh *pBuilding3Mesh = new CFbxModelMesh(pd3dDevice, "../Data/BuildingObject/t_002_b003.data", 1.0f);

	CMesh *pOther1Mesh = new CFbxModelMesh(pd3dDevice, "../Data/BuildingObject/other_001.data", 1.0f);
	CMesh *pDoorMesh = new CFbxModelMesh(pd3dDevice, "../Data/BuildingObject/t002_door001.data", 1.0f);
	CFbxModelMesh *pResponeMesh = new CFbxModelMesh(pd3dDevice, "../Data/CrossRespone.data", 0.1f);
	
	////0812
	//CMesh *pUITeamRespawn = new CBillboardMesh(pd3dDevice, FRAME_BUFFER_WIDTH / 2 - 125 * 1.6f, 100 * 1.6f, 250 * 1.6f, 150 * 1.6f);
	//CMesh *pUIHPCharge = new CBillboardMesh(pd3dDevice, FRAME_BUFFER_WIDTH / 2 - 125 * 1.6f, 200 * 1.6f, 250 * 1.6f, 150 * 1.6f);

	////1. �����޽�
	//pSoldierMesh[IDLE] = new CFbxAnimMesh(pd3dDevice, "Data/Animation/eunbee_idle.data", 0.16f);
	//pSoldierMesh[WALK] = new CFbxAnimMesh(pd3dDevice, "Data/Animation/eunbee_walk.data", 0.16f);
	//pSoldierMesh[BOMB] = new CFbxAnimMesh(pd3dDevice, "Data/Animation/eunbee_bomb.data", 0.16f);
	//pSoldierMesh[DEAD] = new CFbxAnimMesh(pd3dDevice, "Data/Animation/eunbee_dead.data", 0.16f);
	//pSoldierMesh[ATTACK] = new CFbxAnimMesh(pd3dDevice, "Data/Animation/eunbee_attack.data", 0.16f);

	////2. ���� �޽�
	//pNinjaMesh[IDLE] = new CFbxAnimMesh(pd3dDevice, "Data/Animation/Ninja_idle.data", 0.8f);
	//pNinjaMesh[WALK] = new CFbxAnimMesh(pd3dDevice, "Data/Animation/Ninja_walk_inPlace.data", 0.8f);
	//pNinjaMesh[BOMB] = new CFbxAnimMesh(pd3dDevice, "Data/Animation/ninza_throw.data", 0.8f); // ���߿� Attack���� �ٲ��� 
	//pNinjaMesh[DEAD] = new CFbxAnimMesh(pd3dDevice, "Data/Animation/ninza_Death_Forward.data", 0.8f);
	//pNinjaMesh[ATTACK] = new CFbxAnimMesh(pd3dDevice, "Data/Animation/Ninja_attack.data", 0.8f);

	////3. ��ó �޽�
	//pArcherMesh[IDLE] = new CFbxAnimMesh(pd3dDevice, "Data/Animation/eunbee_archer_idle.data", 0.07f);
	//pArcherMesh[WALK] = new CFbxAnimMesh(pd3dDevice, "Data/Animation/eunbee_archer_run.data", 0.07f);
	//pArcherMesh[BOMB] = new CFbxAnimMesh(pd3dDevice, "Data/Animation/eunbee_archer_bomb.data", 0.07f); // ���߿� Attack���� �ٲ��� 
	//pArcherMesh[DEAD] = new CFbxAnimMesh(pd3dDevice, "Data/Animation/eunbee_archer_dead.data", 0.07f);
	//pArcherMesh[ATTACK] = new CFbxAnimMesh(pd3dDevice, "Data/Animation/eunbee_archer_attack.data", 0.07f);
	////-----------------MESH END-----------------//

	//// UI Mesh
	//CMesh *pUICrosshairMesh = new CBillboardMesh(pd3dDevice, FRAME_BUFFER_WIDTH / 2, FRAME_BUFFER_HEIGHT / 2, 50 * 1.6f, 50 * 1.6f);
	//CMesh *pUICharacter1Mesh = new CBillboardMesh(pd3dDevice, -260, -180, 70, 70);
	//CMesh *pUIHPMesh = new CBillboardMesh(pd3dDevice, -130, -180, 150, 10);

	////0812
	//// Sprite Mesh
	//CMesh *pSpriteTestMesh = new CSpriteMesh(pd3dDevice, 10.0f, 14, 0.033f, "Data/SkillAnimation/Special2_");

	//// LandMine Mesh
	//CMesh *pLandMineMesh = new CFbxModelMesh(pd3dDevice, "Data/Bullet/LandMine.data", 1.0f);
	//// Occupied UI
	//CMesh *pInGameTextMesh = new CBillboardMesh(pd3dDevice, 160, 160, 600, 220);

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

#pragma region "CONTAINER MAP"

	// instancingShader
	m_nInstancingShaders = 1;
	m_ppInstancingShaders = new CInstancingShader*[m_nInstancingShaders];

	ifstream in;
	string posX, posY, posZ;
	int posx, posy, posz;
	vector<XMFLOAT3> pos;
	int i = 0;
	int	j = 0;

#pragma region "Container4 Rotation X:-45 Y:0 Z:0"
	m_ppInstancingShaders[0] = new CInstancingShader(4);
	m_ppInstancingShaders[0]->SetMesh(pContainer1Mesh);
	m_ppInstancingShaders[0]->CreateShader(pd3dDevice);
	m_ppInstancingShaders[0]->BuildObjects(pd3dDevice, pNormalMaterial, pContainerTexture1);

	in.open("../Data/MapPosition/container(-90,0,-45).csv");

	while (getline(in, posX, ',') &&
		getline(in, posY, ',') &&
		getline(in, posZ, '\n'))
	{
		posx = atoi(posX.c_str());
		posy = atoi(posY.c_str());
		posz = atoi(posZ.c_str());
		pos.push_back(XMFLOAT3(posx, posy, posz));
	}

	for (auto iterPos = pos.begin(); iterPos != pos.end(); ++iterPos)
	{
		CGameObject *pContainer4Model = new CGameObject(1);
		//pContainer4Model->SetRotate(0, -45, 0);
		pContainer4Model->SetPosition(XMFLOAT3(iterPos->x, iterPos->y, iterPos->z));
		//pContainer4Model->SetBoundingBox(pContainer1Mesh);
		m_ppInstancingShaders[0]->AddObject(pContainer4Model);
	}

	pos.clear();
	in.close();
#pragma endregion

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
	// Ű������ ���� ������ ��ȯ�Ѵ�.
	// ȭ��ǥ Ű�� ������ �÷��̾ ������/����(���� x-��), ��/��(���� z-��)�� �̵��Ѵ�.
	// 'Page Up'�� 'Page Down'Ű�� ������ �÷��̾ ��/�Ʒ�(���� y-��)�� �̵��Ѵ�.
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
	// ���콺�� ĸ�������� ���콺�� �󸶸�ŭ �̵��Ͽ��� ���� ����Ѵ�.
	// ���콺 ���� �Ǵ� ������ ��ư�� ������ ���� �޽����� ó���� �� ���콺�� ĸ���Ͽ���.
	// �׷��Ƿ� ���콺�� ĸ�ĵ� ���� ���콺 ��ư�� ������ ���¸� �ǹ��Ѵ�.
	// ���콺�� �¿� �Ǵ� ���Ϸ� �����̸� �÷��̾ x-�� �Ǵ� y-������ ȸ���Ѵ�.
	if (GetCapture() == m_hWnd)
	{
		// ���콺 Ŀ���� ȭ�鿡�� ���ش�.(������ �ʰ� �Ѵ�.)
		SetCursor(NULL);
		// ���� ���콺 Ŀ���� ��ġ�� �����´�.
		GetCursorPos(&ptCursorPos);
		// ���콺 ��ư�� ���� ä�� ���� ��ġ���� ���� ���콺 Ŀ���� ��ġ���� ������ ���� ���Ѵ�.
		cxDelta = (float)(ptCursorPos.x - m_ptOldCursorPos.x) / 3.0f;
		cyDelta = (float)(ptCursorPos.y - m_ptOldCursorPos.y) / 3.0f;
		SetCursorPos(m_ptOldCursorPos.x, m_ptOldCursorPos.y);
	}

	// �÷��̾ �̵��ϰų�(dwDirection) ȸ���Ѵ�(cxDelta �Ǵ� cyDelta).
	if ((dwDirection != 0) || (cxDelta != 0.0f) || (cyDelta != 0.0f))
	{
		if (cxDelta || cyDelta)
		{
			// cxDelta�� y-���� ȸ���� ��Ÿ���� cyDelta�� x���� ȸ���� ��Ÿ����.
			// ������ ���콺 ��ư�� ������ ��� cxDelta�� z���� ȸ���� ��Ÿ����.
			if (pKeyBuffer[VK_RBUTTON] & 0xF0)
				m_pPlayer->Rotate(cyDelta, 0.0f, -cxDelta);
			else
				m_pPlayer->Rotate(cyDelta, cxDelta, 0.0f);
		}
		// �÷��̾ dwDirection �������� �̵��Ѵ�(�����δ� �ӵ� ���͸� �����Ѵ�.)
		// �̵� �Ÿ��� �ð��� ����ϵ��� �Ѵ�.
		// �÷��̾��� �̵� �ӷ���(50/��)�� �����Ѵ�.
		// ���� �÷��̾��� �̵� �ӷ��� �ִٸ� �� ���� ����Ѵ�.
		if (dwDirection)
			m_pPlayer->Move(dwDirection, 50.0f * fTimeElapsed, true);
	}
	// �÷��̾ ������ �̵��ϰ� ī�޶� �����Ѵ�.
	// �߷°� �������� ������ �ӵ� ���Ϳ� �����Ѵ�.
	m_pPlayer->Update(fTimeElapsed);
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

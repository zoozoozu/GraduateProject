#include "stdafx.h"
<<<<<<< HEAD

#include "Scene/Scene.h"
#include "Scene\Test\TestScene.h"

#include "GameFramework.h"

CGameFramework::CGameFramework()
{
	//m_pd3dDevice = NULL;
	//m_pDXGISwapChain = NULL;
	//m_pd3dRenderTargetView = NULL;
	//m_pd3dDeviceContext = NULL;

	m_nWndClientWidth = FRAME_BUFFER_WIDTH;
	m_nWndClientHeight = FRAME_BUFFER_HEIGHT;

//	m_pScene = NULL;
//	m_pPlayer = NULL;

//	m_pd3dDepthStencilBuffer = NULL;
//	m_pd3dDepthStencilView = NULL;

//	m_pPlayerShader = nullptr;
=======

#include "IndRes/IndRes.h"
#include "Framework/GameFramework.h"

#include "Scene/Scene.h"
#include "Scene/Test/TestScene.h"

#include "Object/HeightMapTerrain/HeightMapTerrain.h"
#include "Mesh/TerrainMesh/TerrainMesh.h"
#include "Object/Player/Player.h"
#include "Shader/PlayerShader/PlayerShader.h"

CGameFramework::CGameFramework()
{
	m_nWndClientWidth = FRAME_BUFFER_WIDTH;
	m_nWndClientHeight = FRAME_BUFFER_HEIGHT;

	m_pPlayer = NULL;

	m_pPlayerShader = nullptr;
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff

	_tcscpy_s(m_pszBuffer, _T("LapProject ("));
}


CGameFramework::~CGameFramework()
{
}

bool CGameFramework::OnCreate(HINSTANCE hInstance, HWND hMainWnd, shared_ptr<CIndRes> indres, shared_ptr<CTimer> timer)
{
	RegisterIndRes(indres);
	RegisterTimer(timer);

	m_hInstance = hInstance;
	m_hWnd = hMainWnd;
	::GetClientRect(hMainWnd, &m_rcClient);

	// Ŭ������ ������ ���ν��� ����
	::SetUserDataPtr(m_hWnd, &m_rcClient);
	m_pIndRes->CreateHwndRenderTarget(hMainWnd, &m_pd2dRenderTarget);

	if (!CreateDirect3DDisplay())
		return(false);

<<<<<<< HEAD
//	BuildObjects();
	BuildScene<CTestScene>(L"Test"s);
=======
	BuildScene<CTestScene>(L"Test"s);
	//BuildObjects();

>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff
	return (true);
}

bool CGameFramework::CreateRenderTargetView()
{
	HRESULT hResult = S_OK;

	ComPtr<ID3D11Texture2D> pd3dBackBuffer{ nullptr };

	if (FAILED(hResult = m_pDXGISwapChain->GetBuffer(0,
		__uuidof(ID3D11Texture2D), (LPVOID*)&pd3dBackBuffer)))
		return(false);

	if (FAILED(hResult = m_pd3dDevice->CreateRenderTargetView(pd3dBackBuffer.Get(),
		NULL, m_pd3dRenderTargetView.GetAddressOf())))
		return(false);

	// ���� Ÿ�ٰ� ���� ũ���� ���� ���۸� �����Ѵ�.
	D3D11_TEXTURE2D_DESC d3dDepthStencilBufferDesc;
	ZeroMemory(&d3dDepthStencilBufferDesc, sizeof(D3D11_TEXTURE2D_DESC));
	d3dDepthStencilBufferDesc.Width = m_nWndClientWidth;
	d3dDepthStencilBufferDesc.Height = m_nWndClientHeight;
	d3dDepthStencilBufferDesc.MipLevels = 1;
	d3dDepthStencilBufferDesc.ArraySize = 1;
	d3dDepthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3dDepthStencilBufferDesc.SampleDesc.Count = 1;
	d3dDepthStencilBufferDesc.SampleDesc.Quality = 0;
	d3dDepthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	d3dDepthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	d3dDepthStencilBufferDesc.CPUAccessFlags = 0;
	d3dDepthStencilBufferDesc.MiscFlags = 0;
	if (FAILED(hResult =
		m_pd3dDevice->CreateTexture2D(&d3dDepthStencilBufferDesc, NULL,
			&m_pd3dDepthStencilBuffer)))
		return(false);

	// ������ ���� ����(Depth Buffer)�� ���� �並 �����Ѵ�.
	D3D11_DEPTH_STENCIL_VIEW_DESC d3dViewDesc;
	ZeroMemory(&d3dViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	d3dViewDesc.Format = d3dDepthStencilBufferDesc.Format;
	d3dViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	d3dViewDesc.Texture2D.MipSlice = 0;
	if (FAILED(hResult =
		m_pd3dDevice->CreateDepthStencilView(m_pd3dDepthStencilBuffer.Get(), &d3dViewDesc,
			&m_pd3dDepthStencilView))) return (false);

<<<<<<< HEAD
	m_pd3dDeviceContext.Get()->OMSetRenderTargets(1, m_pd3dRenderTargetView.GetAddressOf(), m_pd3dDepthStencilView.Get());
=======
	m_pd3dDeviceContext->OMSetRenderTargets(1, &m_pd3dRenderTargetView, m_pd3dDepthStencilView.Get());
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff

	return (true);
}

bool CGameFramework::CreateDirect3DDisplay()
{
	RECT rcClient;
	::GetClientRect(m_hWnd, &rcClient);
	m_nWndClientWidth = rcClient.right - rcClient.left;
	m_nWndClientHeight = rcClient.bottom - rcClient.top;

	UINT dwCreateDeviceFlags = 0;
#ifdef DEBUG
	dwCreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // DEBUG
	
	D3D_DRIVER_TYPE d3dDriverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT nDriverTypes = sizeof(d3dDriverTypes) / sizeof(D3D_DRIVER_TYPE);

	D3D_FEATURE_LEVEL d3dFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};
	UINT nFeatureLevels = sizeof(d3dFeatureLevels) / sizeof(D3D_FEATURE_LEVEL);

	DXGI_SWAP_CHAIN_DESC dxgiSwapChainDesc;
	::ZeroMemory(&dxgiSwapChainDesc, sizeof(dxgiSwapChainDesc));
	dxgiSwapChainDesc.BufferCount = 1;
	dxgiSwapChainDesc.BufferDesc.Width = m_nWndClientWidth;
	dxgiSwapChainDesc.BufferDesc.Height = m_nWndClientHeight;
	dxgiSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	dxgiSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	dxgiSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	dxgiSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	dxgiSwapChainDesc.OutputWindow = m_hWnd;
	dxgiSwapChainDesc.SampleDesc.Count = 1;
	dxgiSwapChainDesc.SampleDesc.Quality = 0;
	dxgiSwapChainDesc.Windowed = TRUE;

	D3D_DRIVER_TYPE nd3dDriverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL nd3dFeatureLevel = D3D_FEATURE_LEVEL_11_0;

	HRESULT hResult = S_OK;

	for (UINT i = 0; i < nDriverTypes; i++)
	{
		nd3dDriverType = d3dDriverTypes[i];
		if (SUCCEEDED(hResult = D3D11CreateDeviceAndSwapChain(NULL,
			nd3dDriverType, NULL, dwCreateDeviceFlags, d3dFeatureLevels, nFeatureLevels,
			D3D11_SDK_VERSION, &dxgiSwapChainDesc, &m_pDXGISwapChain,
			&m_pd3dDevice, &nd3dFeatureLevel, &m_pd3dDeviceContext)))
			break;
	}
	if (!m_pDXGISwapChain || !m_pd3dDevice || !m_pd3dDeviceContext)
		return(false);

	if (!CreateRenderTargetView())
		return(false);

	return(true);
}

<<<<<<< HEAD
//void CGameFramework::BuildObjects()
//{
//	//CShader Ŭ������ ����(static) ��� ������ ����� ��� ���۸� �����Ѵ�.
//	//CShader::CreateShaderVariables(m_pd3dDevice);
//	//CIlluminatedShader::CreateShaderVariables(m_pd3dDevice);
//
//	//m_pScene = new CScene();
//	//m_pScene->BuildObjects(m_pd3dDevice);
//
//	//m_pPlayerShader = new CPlayerShader();
//	//m_pPlayerShader->CreateShader(m_pd3dDevice);
//	//m_pPlayerShader->BuildObjects(m_pd3dDevice);
//	//m_pPlayer = m_pPlayerShader->GetPlayer();
//
//	//CHeightMapTerrain *pTerrain = m_pScene->GetTerrain();
//	//m_pPlayer->SetPosition(XMFLOAT3(pTerrain->GetWidth()*0.5f, pTerrain->GetPeakHeight() + 1000.0f, pTerrain->GetLength()*0.5f));
//
//	////�÷��̾��� ��ġ�� ����� �� ������ ������ ���� �÷��̾��� ��ġ�� ������ �� �ֵ��� �����Ѵ�.
//	//m_pPlayer->SetPlayerUpdatedContext(pTerrain);
//	////ī�޶��� ��ġ�� ����� �� ������ ������ ���� ī�޶��� ��ġ�� ������ �� �ֵ��� �����Ѵ�.
//	//m_pPlayer->SetCameraUpdatedContext(pTerrain);
//
//	//m_pCamera = m_pPlayer->GetCamera();
//	//m_pCamera->SetViewport(m_pd3dDeviceContext, 0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, 0.0f, 1.0f);
//	//m_pCamera->GenerateViewMatrix();
//
//	//m_pScene->SetCamera(m_pCamera);
//}

//void CGameFramework::ReleaseObjects()
//{
//	//CShader Ŭ������ ����(static) ��� ������ ����� ��� ���۸� ��ȯ�Ѵ�.
//	/*CShader::ReleaseShaderVariables();
//
//	if (m_pScene) m_pScene->ReleaseObjects();
//	if (m_pScene) delete m_pScene;
//
//	if (m_pPlayerShader) m_pPlayerShader->ReleaseObjects();
//	if (m_pPlayerShader) delete m_pPlayerShader;*/
//
//}

void CGameFramework::BuildScene(wstring Tag, const unique_ptr<CScene>& scene)
{
	scene->OnCreate(move(Tag), this);
=======
//template<typename CScene>
//void CGameFramework::BuildObjects()
//{
//	//CShader Ŭ������ ����(static) ��� ������ ����� ��� ���۸� �����Ѵ�.
//	CShader::CreateShaderVariables(m_pd3dDevice.Get());
//	CIlluminatedShader::CreateShaderVariables(m_pd3dDevice.Get());
//
//	m_pCurrentScene = new CScene();
//	m_pCurrentScene->BuildObjects(m_pd3dDevice.Get());
//
//	m_pPlayerShader = new CPlayerShader();
//	m_pPlayerShader->CreateShader(m_pd3dDevice.Get());
//	m_pPlayerShader->BuildObjects(m_pd3dDevice.Get());
//	m_pPlayer = m_pPlayerShader->GetPlayer();
//
//	CHeightMapTerrain *pTerrain = m_pCurrentScene->GetTerrain();
//	m_pPlayer->SetPosition(XMFLOAT3(pTerrain->GetWidth()*0.5f, pTerrain->GetPeakHeight() + 1000.0f, pTerrain->GetLength()*0.5f));
//
//	//�÷��̾��� ��ġ�� ����� �� ������ ������ ���� �÷��̾��� ��ġ�� ������ �� �ֵ��� �����Ѵ�.
//	m_pPlayer->SetPlayerUpdatedContext(pTerrain);
//	//ī�޶��� ��ġ�� ����� �� ������ ������ ���� ī�޶��� ��ġ�� ������ �� �ֵ��� �����Ѵ�.
//	m_pPlayer->SetCameraUpdatedContext(pTerrain);
//
//	m_pCamera = m_pPlayer->GetCamera();
//	m_pCamera->SetViewport(m_pd3dDeviceContext.Get(), 0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, 0.0f, 1.0f);
//	m_pCamera->GenerateViewMatrix();
//
//	m_pCurrentScene->SetCamera(m_pCamera);
//}

void CGameFramework::BuildScene(wstring Tag, const unique_ptr<CScene>& scene)
{
	scene->OnCreate(move(Tag), this);
}

void CGameFramework::ReleaseObjects()
{
	//CShader Ŭ������ ����(static) ��� ������ ����� ��� ���۸� ��ȯ�Ѵ�.
	CShader::ReleaseShaderVariables();

	if (m_pCurrentScene) m_pCurrentScene->ReleaseObjects();
	if (m_pCurrentScene) delete m_pCurrentScene;

	if (m_pPlayerShader) m_pPlayerShader->ReleaseObjects();
	if (m_pPlayerShader) delete m_pPlayerShader;

>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff
}

void CGameFramework::ProcessInput()
{
	bool bProcessedByScene = false;
	if (m_pCurrentScene)
<<<<<<< HEAD
		m_pCurrentScene->ProcessInput(m_Timer.GetTimeElapsed());
	//if (!bProcessedByScene)
	//{
	//	static UCHAR pKeyBuffer[256];
	//	DWORD dwDirection = 0;
	//	// Ű������ ���� ������ ��ȯ�Ѵ�.
	//	// ȭ��ǥ Ű�� ������ �÷��̾ ������/����(���� x-��), ��/��(���� z-��)�� �̵��Ѵ�.
	//	// 'Page Up'�� 'Page Down'Ű�� ������ �÷��̾ ��/�Ʒ�(���� y-��)�� �̵��Ѵ�.
	//	if (GetKeyboardState(pKeyBuffer))
	//	{
	//		if (pKeyBuffer['W'] & 0xF0) dwDirection |= DIR_FORWARD;
	//		if (pKeyBuffer['S'] & 0xF0) dwDirection |= DIR_BACKWARD;
	//		if (pKeyBuffer['A'] & 0xF0) dwDirection |= DIR_LEFT;
	//		if (pKeyBuffer['D'] & 0xF0) dwDirection |= DIR_RIGHT;
	//		if (pKeyBuffer[VK_PRIOR] & 0xF0) dwDirection |= DIR_UP;
	//		if (pKeyBuffer[VK_NEXT] & 0xF0) dwDirection |= DIR_DOWN;
	//	}
	//	float cxDelta = 0.0f, cyDelta = 0.0f;
	//	POINT ptCursorPos;
	//	// ���콺�� ĸ�������� ���콺�� �󸶸�ŭ �̵��Ͽ��� ���� ����Ѵ�.
	//	// ���콺 ���� �Ǵ� ������ ��ư�� ������ ���� �޽����� ó���� �� ���콺�� ĸ���Ͽ���.
	//	// �׷��Ƿ� ���콺�� ĸ�ĵ� ���� ���콺 ��ư�� ������ ���¸� �ǹ��Ѵ�.
	//	// ���콺�� �¿� �Ǵ� ���Ϸ� �����̸� �÷��̾ x-�� �Ǵ� y-������ ȸ���Ѵ�.
	//	if (GetCapture() == m_hWnd)
	//	{
	//		// ���콺 Ŀ���� ȭ�鿡�� ���ش�.(������ �ʰ� �Ѵ�.)
	//		SetCursor(NULL);
	//		// ���� ���콺 Ŀ���� ��ġ�� �����´�.
	//		GetCursorPos(&ptCursorPos);
	//		// ���콺 ��ư�� ���� ä�� ���� ��ġ���� ���� ���콺 Ŀ���� ��ġ���� ������ ���� ���Ѵ�.
	//		cxDelta = (float)(ptCursorPos.x - m_ptOldCursorPos.x) / 3.0f;
	//		cyDelta = (float)(ptCursorPos.y - m_ptOldCursorPos.y) / 3.0f;
	//		SetCursorPos(m_ptOldCursorPos.x, m_ptOldCursorPos.y);
	//	}

	//	// �÷��̾ �̵��ϰų�(dwDirection) ȸ���Ѵ�(cxDelta �Ǵ� cyDelta).
	//	if ((dwDirection != 0) || (cxDelta != 0.0f) || (cyDelta != 0.0f))
	//	{
	//		if (cxDelta || cyDelta)
	//		{
	//			// cxDelta�� y-���� ȸ���� ��Ÿ���� cyDelta�� x���� ȸ���� ��Ÿ����.
	//			// ������ ���콺 ��ư�� ������ ��� cxDelta�� z���� ȸ���� ��Ÿ����.
	//			if (pKeyBuffer[VK_RBUTTON] & 0xF0)
	//				m_pPlayer->Rotate(cyDelta, 0.0f, -cxDelta);
	//			else
	//				m_pPlayer->Rotate(cyDelta, cxDelta, 0.0f);
	//		}
	//		// �÷��̾ dwDirection �������� �̵��Ѵ�(�����δ� �ӵ� ���͸� �����Ѵ�.)
	//		// �̵� �Ÿ��� �ð��� ����ϵ��� �Ѵ�.
	//		// �÷��̾��� �̵� �ӷ���(50/��)�� �����Ѵ�.
	//		// ���� �÷��̾��� �̵� �ӷ��� �ִٸ� �� ���� ����Ѵ�.
	//		if (dwDirection)
	//			m_pPlayer->Move(dwDirection, 50.0f * m_Timer.GetTimeElapsed(), true);
	//	}
	//}
	//// �÷��̾ ������ �̵��ϰ� ī�޶� �����Ѵ�.
	//// �߷°� �������� ������ �ӵ� ���Ϳ� �����Ѵ�.
	//m_pPlayer->Update(m_Timer.GetTimeElapsed());
=======
		bProcessedByScene = m_pCurrentScene->ProcessInput();
	if (!bProcessedByScene)
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
				m_pPlayer->Move(dwDirection, 50.0f * m_pTimer->GetTimeElapsed(), true);
		}
	}
	// �÷��̾ ������ �̵��ϰ� ī�޶� �����Ѵ�.
	// �߷°� �������� ������ �ӵ� ���Ϳ� �����Ѵ�.
	m_pPlayer->Update(m_pTimer->GetTimeElapsed());
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff
}

void CGameFramework::AnimateObjects()
{
	if (m_pCurrentScene)
<<<<<<< HEAD
		m_pCurrentScene->AnimateObjects(m_Timer.GetTimeElapsed());
=======
		m_pCurrentScene->AnimateObjects(m_pTimer->GetTimeElapsed());
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff
}

void CGameFramework::FrameAdvance()
{
	m_pTimer->Tick();
	ProcessInput();
	AnimateObjects();

	float fClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
	
	if(m_pd3dRenderTargetView)
<<<<<<< HEAD
		m_pd3dDeviceContext.Get()->ClearRenderTargetView(m_pd3dRenderTargetView.Get(), fClearColor);

	if (m_pd3dDepthStencilView)
		m_pd3dDeviceContext.Get()->ClearDepthStencilView(m_pd3dDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	
	//if (m_pPlayer) m_pPlayer->UpdateShaderVariables(m_pd3dDeviceContext);
	//
	//CCamera *pCamera = (m_pPlayer) ? m_pPlayer->GetCamera() : NULL;
	if (m_pCurrentScene) m_pCurrentScene->Render(m_pd3dDeviceContext.Get());
	
	//3��Ī ī�޶��� �� �÷��̾ �������Ѵ�.
	//if (m_pPlayerShader) m_pPlayerShader->Render(m_pd3dDeviceContext, pCamera);
=======
	m_pd3dDeviceContext->ClearRenderTargetView(m_pd3dRenderTargetView.Get(),
		fClearColor);

	if (m_pd3dDepthStencilView)
		m_pd3dDeviceContext->ClearDepthStencilView(m_pd3dDepthStencilView.Get(),
			D3D11_CLEAR_DEPTH, 1.0f, 0);
	
	if (m_pPlayer) m_pPlayer->UpdateShaderVariables(m_pd3dDeviceContext.Get());
	
	CCamera *pCamera = (m_pPlayer) ? m_pPlayer->GetCamera() : NULL;
	if (m_pCurrentScene) m_pCurrentScene->Render(m_pd3dDeviceContext.Get(), m_pd2dRenderTarget.Get());
	
	//3��Ī ī�޶��� �� �÷��̾ �������Ѵ�.
	if (m_pPlayerShader) m_pPlayerShader->Render(m_pd3dDeviceContext.Get(), pCamera);
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff

	m_pDXGISwapChain->Present(0, 0);
	
	m_pTimer->GetFrameRate(m_pszBuffer + 12, 37);
	::SetWindowText(m_hWnd, m_pszBuffer);
}

bool CGameFramework::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		////���콺 ĸ�ĸ� �ϰ� ���� ���콺 ��ġ�� �����´�.
		//SetCapture(hWnd);
		//GetCursorPos(&m_ptOldCursorPos);
		//break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		//���콺 ĸ�ĸ� �����Ѵ�.
	/*	SetCapture(hWnd);
		GetCursorPos(&m_ptOldCursorPos);*/
	//	ReleaseCapture();
	//	break;
	case WM_MOUSEMOVE:
		break;
	default:
		return false;
	}

	return true;
}

bool CGameFramework::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
<<<<<<< HEAD
=======
			/*��F1�� Ű�� ������ 1��Ī ī�޶�, ��F2�� Ű�� ������ �����̽�-�� ī�޶�� �����Ѵ�, ��F3�� Ű�� ������ 3��Ī ī�޶�� �����Ѵ�.*/
		case VK_F1:
		case VK_F2:
		case VK_F3:
			/*if (m_pPlayer)
			{
				m_pPlayer->ChangeCamera(m_pd3dDevice.Get(), (wParam - VK_F1 + 1), m_pTimer->GetTimeElapsed());
				m_pCamera = m_pPlayer->GetCamera();
				m_pCurrentScene->SetCamera(m_pCamera);
			}*/
			break;

>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;

		default:
			return false;
		}
		break;
	default:
		return false;
	}
	return true;
}

LRESULT CGameFramework::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_SIZE:
	{
		m_nWndClientWidth = LOWORD(lParam);
		m_nWndClientHeight = HIWORD(lParam);

		m_pd3dDeviceContext->OMSetRenderTargets(0, NULL, NULL);

<<<<<<< HEAD
		m_pd3dRenderTargetView = nullptr;
		m_pd3dDepthStencilView = nullptr;
		m_pd3dDepthStencilBuffer = nullptr;
=======
		if (m_pd3dRenderTargetView)
			m_pd3dRenderTargetView.Reset();
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff

		HRESULT hr = m_pDXGISwapChain->ResizeBuffers(2, m_nWndClientWidth,
			m_nWndClientHeight, DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);


		if (hr != S_OK)
		{
			if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
			{
				// �߰� ���� : ��ġ ����� ���� �ʿ�
				MessageBox(m_hWnd, TEXT("Device Lost! ���α׷��� �ٽ� ������ �ּ���."), TEXT("ResizeBuffer Fail!"), MB_OK);
			}
			else MessageBox(m_hWnd, TEXT("�� �� ���� ����! ���α׷��� �ٽ� ������ �ּ���."), TEXT("ResizeBuffer Fail!"), MB_OK);
			DestroyWindow(m_hWnd);
		}

		CreateRenderTargetView();

	/*	CCamera *pCamera = m_pPlayer->GetCamera();
		if (pCamera)
<<<<<<< HEAD
			pCamera->SetViewport(m_pd3dDeviceContext, 0, 0,
				m_nWndClientWidth, m_nWndClientHeight, 0.0f, 1.0f);*/
=======
			pCamera->SetViewport(m_pd3dDeviceContext.Get(), 0, 0,
				m_nWndClientWidth, m_nWndClientHeight, 0.0f, 1.0f);
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff

		break;
	}
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
		break;
	case WM_KEYDOWN:
	case WM_KEYUP:
		OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
		break;
	}
	return(0);
}

void CGameFramework::ChangeScene(std::wstring Tag, bool bDestroyPostScene)
{
	auto pChangeScene = FindScene(Tag);
	if (!pChangeScene) return _DEBUG_ERROR("�������� ���� Scene�� �����Ϸ� �߽��ϴ�!");

	if (m_pCurrentScene && bDestroyPostScene)
	{
		auto& DestroyTag = m_pCurrentScene->Tag();

		m_pCurrentScene = nullptr;

		m_lstScenes.remove_if(
			[&](const unique_ptr<CScene>& s)
		{ return s->FindByTag(DestroyTag); }
		);
	}

	m_pCurrentScene = pChangeScene;
}

CScene * CGameFramework::FindScene(std::wstring Tag)
{
	auto ChangeScene = find_if(begin(m_lstScenes), end(m_lstScenes),
		[&](const unique_ptr<CScene>& s)
	{ return s->FindByTag(Tag); }
	);
	return ChangeScene == end(m_lstScenes) ? nullptr : ChangeScene->get();
}

void CGameFramework::OnDestroy()
{
	//ReleaseObjects();

<<<<<<< HEAD
	//if (m_pd3dDeviceContext)
	//	m_pd3dDeviceContext->ClearState();
	/*if (m_pd3dRenderTargetView)
		m_pd3dRenderTargetView->Release();
	if (m_pd3dDepthStencilBuffer)
		m_pd3dDepthStencilBuffer->Release();
	if (m_pd3dDepthStencilView)
		m_pd3dDepthStencilView->Release();
	if (m_pDXGISwapChain)
		m_pDXGISwapChain->Release();
	if (m_pd3dDeviceContext)
		m_pd3dDeviceContext->Release();
	if (m_pd3dDevice)
		m_pd3dDevice->Release();*/
=======
	if (m_pd3dDeviceContext)
		m_pd3dDeviceContext->ClearState();
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff
}
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

	// 클래스와 윈도우 프로시저 연결
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

	// 렌더 타겟과 같은 크기의 깊이 버퍼를 생성한다.
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

	// 생성한 깊이 버퍼(Depth Buffer)에 대한 뷰를 생성한다.
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
//	//CShader 클래스의 정적(static) 멤버 변수로 선언된 상수 버퍼를 생성한다.
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
//	////플레이어의 위치가 변경될 때 지형의 정보에 따라 플레이어의 위치를 변경할 수 있도록 설정한다.
//	//m_pPlayer->SetPlayerUpdatedContext(pTerrain);
//	////카메라의 위치가 변경될 때 지형의 정보에 따라 카메라의 위치를 변경할 수 있도록 설정한다.
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
//	//CShader 클래스의 정적(static) 멤버 변수로 선언된 상수 버퍼를 반환한다.
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
//	//CShader 클래스의 정적(static) 멤버 변수로 선언된 상수 버퍼를 생성한다.
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
//	//플레이어의 위치가 변경될 때 지형의 정보에 따라 플레이어의 위치를 변경할 수 있도록 설정한다.
//	m_pPlayer->SetPlayerUpdatedContext(pTerrain);
//	//카메라의 위치가 변경될 때 지형의 정보에 따라 카메라의 위치를 변경할 수 있도록 설정한다.
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
	//CShader 클래스의 정적(static) 멤버 변수로 선언된 상수 버퍼를 반환한다.
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
	//	// 키보드의 상태 정보를 반환한다.
	//	// 화살표 키를 누르면 플레이어를 오른쪽/왼쪽(로컬 x-축), 앞/뒤(로컬 z-축)로 이동한다.
	//	// 'Page Up'과 'Page Down'키를 누르면 플레이어를 위/아래(로컬 y-축)로 이동한다.
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
	//	// 마우스를 캡쳐했으면 마우스가 얼마만큼 이동하였는 가를 계산한다.
	//	// 마우스 왼쪽 또는 오른쪽 버튼이 눌러질 때의 메시지를 처리할 때 마우스를 캡쳐하였다.
	//	// 그러므로 마우스가 캡쳐된 것은 마우스 버튼이 눌려진 상태를 의미한다.
	//	// 마우스를 좌우 또는 상하로 움직이면 플레이어를 x-축 또는 y-축으로 회전한다.
	//	if (GetCapture() == m_hWnd)
	//	{
	//		// 마우스 커서를 화면에서 없앤다.(보이지 않게 한다.)
	//		SetCursor(NULL);
	//		// 현재 마우스 커서의 위치를 가져온다.
	//		GetCursorPos(&ptCursorPos);
	//		// 마우스 버튼이 눌린 채로 이전 위치에서 현재 마우스 커서의 위치까지 움직인 양을 구한다.
	//		cxDelta = (float)(ptCursorPos.x - m_ptOldCursorPos.x) / 3.0f;
	//		cyDelta = (float)(ptCursorPos.y - m_ptOldCursorPos.y) / 3.0f;
	//		SetCursorPos(m_ptOldCursorPos.x, m_ptOldCursorPos.y);
	//	}

	//	// 플레이어를 이동하거나(dwDirection) 회전한다(cxDelta 또는 cyDelta).
	//	if ((dwDirection != 0) || (cxDelta != 0.0f) || (cyDelta != 0.0f))
	//	{
	//		if (cxDelta || cyDelta)
	//		{
	//			// cxDelta는 y-축의 회전을 나타내고 cyDelta는 x축의 회전을 나타낸다.
	//			// 오른쪽 마우스 버튼이 눌려진 경우 cxDelta는 z축의 회전을 나타낸다.
	//			if (pKeyBuffer[VK_RBUTTON] & 0xF0)
	//				m_pPlayer->Rotate(cyDelta, 0.0f, -cxDelta);
	//			else
	//				m_pPlayer->Rotate(cyDelta, cxDelta, 0.0f);
	//		}
	//		// 플레이어를 dwDirection 방향으로 이동한다(실제로는 속도 벡터를 변경한다.)
	//		// 이동 거리는 시간에 비례하도록 한다.
	//		// 플레이어의 이동 속력은(50/초)로 가정한다.
	//		// 만약 플레이어의 이동 속력이 있다면 그 값을 사용한다.
	//		if (dwDirection)
	//			m_pPlayer->Move(dwDirection, 50.0f * m_Timer.GetTimeElapsed(), true);
	//	}
	//}
	//// 플레이어를 실제로 이동하고 카메라를 갱신한다.
	//// 중력과 마찰력의 영향을 속도 벡터에 적용한다.
	//m_pPlayer->Update(m_Timer.GetTimeElapsed());
=======
		bProcessedByScene = m_pCurrentScene->ProcessInput();
	if (!bProcessedByScene)
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
				m_pPlayer->Move(dwDirection, 50.0f * m_pTimer->GetTimeElapsed(), true);
		}
	}
	// 플레이어를 실제로 이동하고 카메라를 갱신한다.
	// 중력과 마찰력의 영향을 속도 벡터에 적용한다.
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
	
	//3인칭 카메라일 때 플레이어를 렌더링한다.
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
	
	//3인칭 카메라일 때 플레이어를 렌더링한다.
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
		////마우스 캡쳐를 하고 현재 마우스 위치를 가져온다.
		//SetCapture(hWnd);
		//GetCursorPos(&m_ptOldCursorPos);
		//break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		//마우스 캡쳐를 해제한다.
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
			/*‘F1’ 키를 누르면 1인칭 카메라, ‘F2’ 키를 누르면 스페이스-쉽 카메라로 변경한다, ‘F3’ 키를 누르면 3인칭 카메라로 변경한다.*/
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
				// 추가 사항 : 장치 재생성 구현 필요
				MessageBox(m_hWnd, TEXT("Device Lost! 프로그램을 다시 실행해 주세요."), TEXT("ResizeBuffer Fail!"), MB_OK);
			}
			else MessageBox(m_hWnd, TEXT("알 수 없는 이유! 프로그램을 다시 실행해 주세요."), TEXT("ResizeBuffer Fail!"), MB_OK);
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
	if (!pChangeScene) return _DEBUG_ERROR("생성되지 않은 Scene을 참조하려 했습니다!");

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
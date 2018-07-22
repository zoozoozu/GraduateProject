#include "stdafx.h"

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

	_tcscpy_s(m_pszBuffer, _T("LapProject ("));
}


CGameFramework::~CGameFramework()
{
}

bool CGameFramework::OnCreate(HINSTANCE hInstance, HWND hMainWnd)
{
	m_hInstance = hInstance;
	m_hWnd = hMainWnd;

	if (!CreateDirect3DDisplay())
		return(false);

//	BuildObjects();
	BuildScene<CTestScene>(L"Test"s);
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

	m_pd3dDeviceContext.Get()->OMSetRenderTargets(1, m_pd3dRenderTargetView.GetAddressOf(), m_pd3dDepthStencilView.Get());

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
}

void CGameFramework::ProcessInput()
{
	if (m_pCurrentScene)
		m_pCurrentScene->ProcessInput(m_Timer.GetTimeElapsed());
}

void CGameFramework::AnimateObjects()
{
	if (m_pCurrentScene)
		m_pCurrentScene->AnimateObjects(m_Timer.GetTimeElapsed());
}

void CGameFramework::FrameAdvance()
{
	m_Timer.Tick();
	ProcessInput();
	AnimateObjects();

	float fClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
	
	if(m_pd3dRenderTargetView)
		m_pd3dDeviceContext.Get()->ClearRenderTargetView(m_pd3dRenderTargetView.Get(), fClearColor);

	if (m_pd3dDepthStencilView)
		m_pd3dDeviceContext.Get()->ClearDepthStencilView(m_pd3dDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	
	//if (m_pPlayer) m_pPlayer->UpdateShaderVariables(m_pd3dDeviceContext);
	//
	//shared_ptr<CCamera>pCamera = (m_pPlayer) ? m_pPlayer->GetCamera() : NULL;
	if (m_pCurrentScene) m_pCurrentScene->Render(m_pd3dDeviceContext.Get());
	
	//3인칭 카메라일 때 플레이어를 렌더링한다.
	//if (m_pPlayerShader) m_pPlayerShader->Render(m_pd3dDeviceContext, pCamera);

	m_pDXGISwapChain->Present(0, 0);
	
	m_Timer.GetFrameRate(m_pszBuffer + 12, 37);
	::SetWindowText(m_hWnd, m_pszBuffer);
}

bool CGameFramework::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONUP:
		break;
	default:
		break;
	}

	return(false);
}

bool CGameFramework::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
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
	return(false);
}

LRESULT CGameFramework::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	// 선처리 구문 : 개별 Scene에서 처리할 것인지 확인
	switch (nMessageID)
	{
	case WM_SIZE:
	{
		m_nWndClientWidth = LOWORD(lParam);
		m_nWndClientHeight = HIWORD(lParam);

		m_pd3dDeviceContext->OMSetRenderTargets(0, NULL, NULL);

		m_pd3dRenderTargetView = nullptr;
		m_pd3dDepthStencilView = nullptr;
		m_pd3dDepthStencilBuffer = nullptr;

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

		/*	shared_ptr<CCamera>pCamera = m_pPlayer->GetCamera();
			if (pCamera)
				pCamera->SetViewport(m_pd3dDeviceContext, 0, 0,
					m_nWndClientWidth, m_nWndClientHeight, 0.0f, 1.0f);*/

		break;
	}
	default:
		if (m_pCurrentScene) if (m_pCurrentScene->OnProcessingWindowMessage(hWnd, nMessageID, wParam, lParam)) break;
		else return 0;
	}

	// 후처리 구문 : Scene에서 처리되지 않고 남는 부분을 처리
	switch (nMessageID)
	{
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

	default:
		break;
	}

	return DefWindowProc(hWnd, nMessageID, wParam, lParam);
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
}
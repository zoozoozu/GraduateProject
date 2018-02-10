#pragma once

#include "Scene\Scene.h"
#include "Timer/Timer.h"

class CPlayer;
class CPlayerShader;

class CGameFramework
{
private:
	HWND		m_hWnd							{ nullptr };
	HINSTANCE	m_hInstance						{ nullptr };

	int m_nWndClientWidth;
	int m_nWndClientHeight;

	ComPtr<ID3D11Device>				m_pd3dDevice					{ nullptr };
	ComPtr<IDXGISwapChain>				m_pDXGISwapChain				{ nullptr };
	ComPtr<ID3D11DeviceContext>			m_pd3dDeviceContext				{ nullptr };
	ComPtr<ID3D11RenderTargetView>		m_pd3dRenderTargetView			{ nullptr };
	
	// 깊이 버퍼 객체 인터페이스와 뷰에 대한 포인터이다.
	ComPtr<ID3D11Texture2D>				m_pd3dDepthStencilBuffer		{ nullptr };
	ComPtr<ID3D11DepthStencilView>		m_pd3dDepthStencilView			{ nullptr };

	CTimer m_Timer;

	list<unique_ptr<CScene>>			m_lstScenes;
	CScene*								m_pCurrentScene					{ nullptr };
	
	_TCHAR m_pszBuffer[50];

public:
	CGameFramework();
	~CGameFramework();

	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	void OnDestroy();

	bool CreateRenderTargetView();
	bool CreateDirect3DDisplay();

	// Scene Make
	template<typename Scene>
	Scene* BuildScene(wstring Tag, bool bChangeThis = true)
	{
		// Debug, Release 상관없이 컴파일 된다.
		static_assert(is_base_of_v<CScene, Scene>, "Scene is must be based on CScene!");

		unique_ptr<CScene> scene{ make_unique<Scene>() };
		BuildScene(Tag, scene);
		m_lstScenes.push_back(move(scene));
		if (bChangeThis) ChangeScene(Tag);

		return static_cast<Scene*>(FindScene(Tag));
	}

private:
	void BuildScene(wstring Tag, const unique_ptr<CScene>& scene);

public:
	//void BuildObjects();
	//void ReleaseObjects();

	void ProcessInput();
	void AnimateObjects();
	void FrameAdvance();

	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID,
		WPARAM wParam, LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID,
		WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID,
		WPARAM wParam, LPARAM lParam);

	void ChangeScene(std::wstring Tag, bool bDestroyPostScene = false);
	CScene* FindScene(std::wstring Tag);

	// Getter
public:
	HWND GethWnd()										const { return m_hWnd; }
	ComPtr<ID3D11Device> GetD3DDevice()					const { return m_pd3dDevice; }
	ComPtr<ID3D11DeviceContext> GetD3DDeviceContext()	const { return m_pd3dDeviceContext; }
};


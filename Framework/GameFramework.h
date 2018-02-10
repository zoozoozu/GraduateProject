#pragma once

#include "Scene\Scene.h"
#include "Timer/Timer.h"

class CIndRes;
class CPlayer;
class CPlayerShader;
class CCamera;

class CGameFramework
{
private:
<<<<<<< HEAD
	HWND		m_hWnd							{ nullptr };
	HINSTANCE	m_hInstance						{ nullptr };
=======
	HINSTANCE								m_hInstance							{ nullptr };
	HWND									m_hWnd								{ nullptr };
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff

	shared_ptr<CIndRes>						m_pIndRes							{ nullptr };
	shared_ptr<CTimer>						m_pTimer							{ nullptr };

	D2D_RECT_L								m_rcClient;
	int										m_nWndClientWidth;
	int										m_nWndClientHeight;

	ComPtr<ID3D11Device>					m_pd3dDevice						{ nullptr };
	ComPtr<IDXGISwapChain>					m_pDXGISwapChain					{ nullptr };
	ComPtr<ID3D11DeviceContext>				m_pd3dDeviceContext					{ nullptr };
	ComPtr<ID3D11RenderTargetView>			m_pd3dRenderTargetView				{ nullptr };

	ComPtr<ID2D1HwndRenderTarget>			m_pd2dRenderTarget					{ nullptr };

<<<<<<< HEAD
	ComPtr<ID3D11Device>				m_pd3dDevice					{ nullptr };
	ComPtr<IDXGISwapChain>				m_pDXGISwapChain				{ nullptr };
	ComPtr<ID3D11DeviceContext>			m_pd3dDeviceContext				{ nullptr };
	ComPtr<ID3D11RenderTargetView>		m_pd3dRenderTargetView			{ nullptr };
	
	// 깊이 버퍼 객체 인터페이스와 뷰에 대한 포인터이다.
	ComPtr<ID3D11Texture2D>				m_pd3dDepthStencilBuffer		{ nullptr };
	ComPtr<ID3D11DepthStencilView>		m_pd3dDepthStencilView			{ nullptr };

	CTimer m_Timer;
=======
	// 깊이 버퍼 객체 인터페이스와 뷰에 대한 포인터이다.
	ComPtr<ID3D11Texture2D>					m_pd3dDepthStencilBuffer			{ nullptr };
	ComPtr<ID3D11DepthStencilView>			m_pd3dDepthStencilView				{ nullptr };

	list<unique_ptr<CScene>>				m_lstScenes;
	CScene*									m_pCurrentScene						{ nullptr };

	_TCHAR m_pszBuffer[50];

	CPlayer *m_pPlayer;
	CCamera *m_pCamera;
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff

	list<unique_ptr<CScene>>			m_lstScenes;
	CScene*								m_pCurrentScene					{ nullptr };
	
	_TCHAR m_pszBuffer[50];

private:
	void BuildScene(wstring Tag, const unique_ptr<CScene>& scene);

public:
	CGameFramework();
	~CGameFramework();

	// Direct2D
	void RegisterIndRes(shared_ptr<CIndRes> indres) { m_pIndRes = indres; }
	void RegisterTimer(shared_ptr<CTimer> timer) { m_pTimer = timer; }

	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd, shared_ptr<CIndRes> indres, shared_ptr<CTimer> timer);
	void OnDestroy();

	bool CreateRenderTargetView();
	bool CreateDirect3DDisplay();
<<<<<<< HEAD

	// Scene Make
	template<typename Scene>
	Scene* BuildScene(wstring Tag, bool bChangeThis = true)
=======
	
	template<typename Scene>
	CScene* BuildScene(wstring Tag, bool bChangeThis = true)
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff
	{
		// Debug, Release 상관없이 컴파일 된다.
		static_assert(is_base_of_v<CScene, Scene>, "Scene is must be based on CScene!");

		unique_ptr<CScene> scene{ make_unique<Scene>() };
		BuildScene(Tag, scene);
		m_lstScenes.push_back(move(scene));
		if (bChangeThis) ChangeScene(Tag);

		return static_cast<Scene*>(FindScene(Tag));
	}

<<<<<<< HEAD
private:
	void BuildScene(wstring Tag, const unique_ptr<CScene>& scene);

public:
	//void BuildObjects();
	//void ReleaseObjects();
=======
	//Scene* BuildObjects(wstring Tag, bool bChangeThis = true);
	
	void ReleaseObjects();
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff

	void ProcessInput();
	void AnimateObjects();
	void FrameAdvance();

	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID,
		WPARAM wParam, LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID,
		WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID,
		WPARAM wParam, LPARAM lParam);
<<<<<<< HEAD

	void ChangeScene(std::wstring Tag, bool bDestroyPostScene = false);
	CScene* FindScene(std::wstring Tag);

	// Getter
public:
	HWND GethWnd()										const { return m_hWnd; }
	ComPtr<ID3D11Device> GetD3DDevice()					const { return m_pd3dDevice; }
	ComPtr<ID3D11DeviceContext> GetD3DDeviceContext()	const { return m_pd3dDeviceContext; }
};
=======
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff

	void ChangeScene(std::wstring Tag, bool bDestroyPostScene = false);
	CScene* FindScene(std::wstring Tag);

public:
	HWND GethWnd()									const { return m_hWnd; }
	D2D_RECT_L GetClientSize()						const { return m_rcClient; }
	shared_ptr<CIndRes> GetIndRes()					const { return m_pIndRes; }
	ComPtr<ID2D1HwndRenderTarget> GetRenderTarget() const { return m_pd2dRenderTarget; }
};

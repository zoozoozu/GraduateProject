#pragma once

#include "Scene/Scene.h"
#include "Timer/Timer.h"

class CIndRes;
class CPlayer;
class CPlayerShader;
class CCamera;

class CGameFramework
{
private:
	HINSTANCE								m_hInstance							{ nullptr };
	HWND									m_hWnd								{ nullptr };

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

	// 깊이 버퍼 객체 인터페이스와 뷰에 대한 포인터이다.
	ComPtr<ID3D11Texture2D>					m_pd3dDepthStencilBuffer			{ nullptr };
	ComPtr<ID3D11DepthStencilView>			m_pd3dDepthStencilView				{ nullptr };

	list<unique_ptr<CScene>>				m_lstScenes;
	CScene*									m_pCurrentScene						{ nullptr };

	_TCHAR m_pszBuffer[50];

	CPlayer *m_pPlayer;
	CCamera *m_pCamera;

	//마지막으로 마우스 버튼을 클릭할 때의 마우스 커서의 위치이다.
	POINT	m_ptOldCursorPos;

	CPlayerShader *m_pPlayerShader;

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
	
	template<typename Scene>
	CScene* BuildScene(wstring Tag, bool bChangeThis = true)
	{
		// Debug, Release 상관없이 컴파일 된다.
		static_assert(is_base_of_v<CScene, Scene>, "Scene is must be based on CScene!");

		unique_ptr<CScene> scene{ make_unique<Scene>() };
		BuildScene(Tag, scene);
		m_lstScenes.push_back(move(scene));
		if (bChangeThis) ChangeScene(Tag);

		return static_cast<Scene*>(FindScene(Tag));
	}

	//Scene* BuildObjects(wstring Tag, bool bChangeThis = true);
	
	void ReleaseObjects();

	void ProcessInput();
	void AnimateObjects();
	void FrameAdvance();

	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID,
		WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID,
		WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID,
		WPARAM wParam, LPARAM lParam);

	void ChangeScene(std::wstring Tag, bool bDestroyPostScene = false);
	CScene* FindScene(std::wstring Tag);

public:
	HWND GethWnd()									const { return m_hWnd; }
	D2D_RECT_L GetClientSize()						const { return m_rcClient; }
	shared_ptr<CIndRes> GetIndRes()					const { return m_pIndRes; }
	ComPtr<ID2D1HwndRenderTarget> GetRenderTarget() const { return m_pd2dRenderTarget; }
};

#pragma once

#include "Scene/Scene.h"
#include "Timer/Timer.h"

class CPlayer;
class CPlayerShader;

class CGameFramework
{
private:
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;

	int m_nWndClientWidth;
	int m_nWndClientHeight;

	ID3D11Device *m_pd3dDevice;
	IDXGISwapChain *m_pDXGISwapChain;
	ID3D11DeviceContext *m_pd3dDeviceContext;
	ID3D11RenderTargetView *m_pd3dRenderTargetView;
	// ���� ���� ��ü �������̽��� �信 ���� �������̴�.
	ID3D11Texture2D *m_pd3dDepthStencilBuffer;
	ID3D11DepthStencilView *m_pd3dDepthStencilView;

	CTimer m_Timer;
	CScene *m_pScene;
	_TCHAR m_pszBuffer[50];

	CPlayer *m_pPlayer;
	CCamera *m_pCamera;

	//���������� ���콺 ��ư�� Ŭ���� ���� ���콺 Ŀ���� ��ġ�̴�.
	POINT	m_ptOldCursorPos;

	CPlayerShader *m_pPlayerShader;

public:
	CGameFramework();
	~CGameFramework();

	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	void OnDestroy();

	bool CreateRenderTargetView();
	bool CreateDirect3DDisplay();

	void BuildObjects();
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
};


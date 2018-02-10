#pragma once

class CGameFramework;


class CScene
{
protected:
	CGameFramework*			m_pFramework{ nullptr };
	HWND					m_hWnd		{ NULL };

	wstring					m_strTag;

public:
	CScene();
	virtual ~CScene();

	virtual bool OnCreate(wstring&& tag, CGameFramework* pFramework);

	virtual bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void BuildObjects(ID3D11Device *pd3dDevice) {};
	virtual void ProcessInput(float fTimeElapsed) = 0;
	virtual void AnimateObjects(float fTimeElapsed) = 0;
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext) = 0;
	
	
	CGameFramework* Framework() const { return m_pFramework; }

	bool FindByTag(const wstring& Tag) const { return Tag == m_strTag; }

	const wstring& Tag() const { return m_strTag; }

	

};
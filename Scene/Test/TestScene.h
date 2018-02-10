#pragma once
<<<<<<< HEAD
#include "Scene\Scene.h"
#include "Camera\Camera.h"

#include "Shader\PlayerShader\PlayerShader.h"
#include "Shader\Shader.h"
=======

#include "Scene/Scene.h"
#include "Shader/Shader.h"
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff

#define MAX_LIGHTS		4 
#define POINT_LIGHT		1.0f
#define SPOT_LIGHT		2.0f
#define DIRECTIONAL_LIGHT	3.0f

class CHeightMapTerrain;
class CAABBRenderShader;

//1���� ������ ǥ���ϴ� ����ü�̴�. 
struct LIGHT
{
	XMFLOAT4 m_d3dxcAmbient;
	XMFLOAT4 m_d3dxcDiffuse;
	XMFLOAT4 m_d3dxcSpecular;
	XMFLOAT3 m_d3dxvPosition;
	float m_fRange;
	XMFLOAT3 m_d3dxvDirection;
	float m_nType;
	XMFLOAT3 m_d3dxvAttenuation;
	float m_fFalloff;
	float m_fTheta; //cos(m_fTheta)
	float m_fPhi; //cos(m_fPhi)
	float m_bEnable;
	float padding;
};

//��� ���۴� ũ�Ⱑ �ݵ�� 16 ����Ʈ�� ����� �Ǿ�� �Ѵ�. 
struct LIGHTS
{
	LIGHT m_pLights[MAX_LIGHTS];
	XMFLOAT4 m_d3dxcGlobalAmbient;
	XMFLOAT4 m_d3dxvCameraPosition;
};

<<<<<<< HEAD
class CTestScene
	:public CScene
=======
class CTestScene 
	: public CScene
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff
{
private:
	// ���� ���̴����� ����Ʈ(�迭)�̴�.
	CShader **m_ppShaders;
	int m_nShaders;

private:
	LIGHTS *m_pLights;
	ID3D11Buffer *m_pd3dcbLights;
	
<<<<<<< HEAD
	CAABBRenderShader *m_aabbShader;

	CPlayer *m_pPlayer;
	CPlayerShader *m_pPlayerShader;

	CCamera *m_pCamera;

	//���������� ���콺 ��ư�� Ŭ���� ���� ���콺 Ŀ���� ��ġ�̴�.
	POINT	m_ptOldCursorPos;
=======
	CCamera *m_pCamera;
	CAABBRenderShader *m_aabbShader;
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff

public:
	void CreateShaderVariables(ID3D11Device *pd3dDevice);
	void UpdateShaderVariable(ID3D11DeviceContext *pd3dDeviceContext, LIGHTS *pLights);
	void ReleaseShaderVariables();

public:
	CTestScene();
	virtual ~CTestScene();

<<<<<<< HEAD
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) override;
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) override;
	bool OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)	override;

	bool OnCreate(wstring&& tag, CGameFramework* pFramework) override;
	void BuildObjects(ID3D11Device* pd3dDevice) override;
	void ProcessInput(float fTimeElasped) override;
	void AnimateObjects(float fTimeElapsed) override;
	void Render(ID3D11DeviceContext *pd3dDeviceContext) override;

	void ReleaseObjects();
=======
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID,
		WPARAM wParam, LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID,
		WPARAM wParam, LPARAM lParam);
	bool OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);


	void BuildObjects(ID3D11Device *pd3dDevice);
	void ReleaseObjects();
	bool ProcessInput();
	void AnimateObjects(float fTimeElapsed);
	void Render(ID3D11DeviceContext *pd3dDeviceContext, ID2D1HwndRenderTarget *pd2dRenderTarget);
>>>>>>> 09acc2ba2b1a19d22b017c96c6b6b91f802066ff

	void SetCamera(CCamera *pCamera) { m_pCamera = pCamera; }

	CHeightMapTerrain *GetTerrain();
};


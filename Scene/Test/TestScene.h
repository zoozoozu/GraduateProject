#pragma once
#include "Scene\Scene.h"
#include "Camera\Camera.h"

#include "Shader\PlayerShader\PlayerShader.h"
#include "Shader\Shader.h"

#define MAX_LIGHTS		4 
#define POINT_LIGHT		1.0f
#define SPOT_LIGHT		2.0f
#define DIRECTIONAL_LIGHT	3.0f

class CHeightMapTerrain;
class CAABBRenderShader;

//1개의 조명을 표현하는 구조체이다. 
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

//상수 버퍼는 크기가 반드시 16 바이트의 배수가 되어야 한다. 
struct LIGHTS
{
	LIGHT m_pLights[MAX_LIGHTS];
	XMFLOAT4 m_d3dxcGlobalAmbient;
	XMFLOAT4 m_d3dxvCameraPosition;
};

class CTestScene
	:public CScene
{
private:
	// 씬은 쉐이더들의 리스트(배열)이다.
	CShader **m_ppShaders;
	int m_nShaders;

private:
	LIGHTS *m_pLights;
	ID3D11Buffer *m_pd3dcbLights;
	
	CAABBRenderShader *m_aabbShader;

	CPlayer *m_pPlayer;
	CPlayerShader *m_pPlayerShader;

	CCamera *m_pCamera;

	//마지막으로 마우스 버튼을 클릭할 때의 마우스 커서의 위치이다.
	POINT	m_ptOldCursorPos;

public:
	void CreateShaderVariables(ID3D11Device *pd3dDevice);
	void UpdateShaderVariable(ID3D11DeviceContext *pd3dDeviceContext, LIGHTS *pLights);
	void ReleaseShaderVariables();

public:
	CTestScene();
	virtual ~CTestScene();

	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) override;
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) override;
	bool OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)	override;

	bool OnCreate(wstring&& tag, CGameFramework* pFramework) override;
	void BuildObjects(ID3D11Device* pd3dDevice) override;
	void ProcessInput(float fTimeElasped) override;
	void AnimateObjects(float fTimeElapsed) override;
	void Render(ID3D11DeviceContext *pd3dDeviceContext) override;

	void ReleaseObjects();

	void SetCamera(CCamera *pCamera) { m_pCamera = pCamera; }

	CHeightMapTerrain *GetTerrain();
};


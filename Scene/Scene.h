#pragma once
#include "Shader/Shader.h"

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

class CScene
{
private:
	// ���� ���̴����� ����Ʈ(�迭)�̴�.
	CShader **m_ppShaders;
	int m_nShaders;

private:
	LIGHTS *m_pLights;
	ID3D11Buffer *m_pd3dcbLights;
	
	CCamera *m_pCamera;
	CAABBRenderShader *m_aabbShader;

public:
	void CreateShaderVariables(ID3D11Device *pd3dDevice);
	void UpdateShaderVariable(ID3D11DeviceContext *pd3dDeviceContext, LIGHTS *pLights);
	void ReleaseShaderVariables();

public:
	CScene();
	~CScene();

	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID,
		WPARAM wParam, LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID,
		WPARAM wParam, LPARAM lParam);

	void BuildObjects(ID3D11Device *pd3dDevice);
	void ReleaseObjects();

	bool ProcessInput();
	void AnimateObjects(float fTimeElapsed);
	void Render(ID3D11DeviceContext *pd3dDeviceContext,
		CCamera *pCamera);

	void SetCamera(CCamera *pCamera) { m_pCamera = pCamera; }

	CHeightMapTerrain *GetTerrain();
};


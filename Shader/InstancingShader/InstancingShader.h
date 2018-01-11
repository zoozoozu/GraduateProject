#pragma once
#include "Shader/Shader.h"

class CHeightMapTerrain;

class CInstancingShader :
	public CTexturedIlluminatedShader
{
public:
	CInstancingShader();
	virtual ~CInstancingShader();

	virtual void CreateShader(ID3D11Device *pd3dDevice);
	virtual void UpdateShaderVariables(ID3D11DeviceContext *pd3dDeviceContext);

	virtual void BuildObjects(ID3D11Device *pd3dDevice, CHeightMapTerrain *pHeightMapTerrain,
		CMaterial *pMaterial, CTexture *pTexture, int k);
	virtual void ReleaseObjects();

	virtual void AnimateObjects(float fTimeElapsed);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext, CCamera *pCamera);

	int m_nObjects;
	CGameObject **m_ppObjects;

	// 인스턴싱으로 그릴 메쉬에 대한 포인터이다.
	CMesh *m_pMesh;

	// 인스턴싱으로 그릴 객체의 월드 변환 행렬들의 배열을 저장할 상수 버퍼이다.
	ID3D11Buffer *m_pd3dcbInstanceMatrices;
	UINT m_nMatrixBufferStride;
	UINT m_nMatrixBufferOffset;

	CTexture *m_pTexture;
	CMaterial *m_pMaterial;

public:
	void SetMesh(CMesh *pMesh);
	//인스턴싱 버퍼를 생성한다.
	ID3D11Buffer *CreateInstanceBuffer(ID3D11Device *pd3dDevice, int nObjects, UINT nBufferStride, void *pBufferData);

};


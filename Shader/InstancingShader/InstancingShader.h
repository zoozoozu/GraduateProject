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

	// �ν��Ͻ����� �׸� �޽��� ���� �������̴�.
	CMesh *m_pMesh;

	// �ν��Ͻ����� �׸� ��ü�� ���� ��ȯ ��ĵ��� �迭�� ������ ��� �����̴�.
	ID3D11Buffer *m_pd3dcbInstanceMatrices;
	UINT m_nMatrixBufferStride;
	UINT m_nMatrixBufferOffset;

	CTexture *m_pTexture;
	CMaterial *m_pMaterial;

public:
	void SetMesh(CMesh *pMesh);
	//�ν��Ͻ� ���۸� �����Ѵ�.
	ID3D11Buffer *CreateInstanceBuffer(ID3D11Device *pd3dDevice, int nObjects, UINT nBufferStride, void *pBufferData);

};


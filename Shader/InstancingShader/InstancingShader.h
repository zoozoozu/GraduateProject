#pragma once
#include "Shader/Shader.h"

class CHeightMapTerrain;

class CInstancingShader :
	public CTexturedIlluminatedShader
{
protected:
	UINT m_nInstanceBufferStride;
	UINT m_nInstanceBufferOffset;

	ID3D11Buffer *m_pd3dInstanceBuffer;

public:
	CInstancingShader(int nObjects);
	virtual ~CInstancingShader();

	virtual void SetMesh(CMesh *pMesh);

	virtual void CreateShader(ID3D11Device *pd3dDevice);
	virtual void BuildObjects(ID3D11Device *pd3dDevice, CMaterial *pMaterial, CTexture *pTexture);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext, shared_ptr<CCamera>pCamera);

	//인스턴싱 버퍼를 생성한다.
	ID3D11Buffer *CreateInstanceBuffer(ID3D11Device *pd3dDevice, int nObjects, UINT nBufferStride, void *pBufferData);
};


#pragma once
#include "Shader/InstancingShader/InstancingShader.h"

class AABB;

class CAABBRenderShader :
	public CInstancingShader
{
private:
	ID3D11Buffer					*m_pd3dVSBuffer;
	AABB							m_pd3dcbAABB;

public:
	CAABBRenderShader(CMesh *pMesh, int nObjects);
	CAABBRenderShader(CMesh *pMesh);
	CAABBRenderShader(int nObjects = 1);
	virtual ~CAABBRenderShader();
	virtual void CreateShader(ID3D11Device *pd3dDevice);

	void UpdateConstBuffer(ID3D11DeviceContext *pd3dDeviceContext);
	void Render(ID3D11DeviceContext *pd3dDeviceContext, CCamera *pCamera, AABB aabb, CGameObject *pGameObject);

};


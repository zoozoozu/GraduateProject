#pragma once
#include "Object/Object.h"

class CBillboardObject
	: public CGameObject
{
	CCamera*	m_pCamera;
public:
	CBillboardObject(CCamera* pCamera, int nMeshes);
	virtual void SetCamera(CCamera* pCamera) { m_pCamera = pCamera; }
	void SetLookAt(XMVECTOR& d3dxvTarget);
	virtual void Animate(float fTimeElapsed);
};

#pragma once
#include "Object/Object.h"
class CSkyBox :
	public CGameObject
{
public:
	CSkyBox(ID3D11Device *pd3dDevice);
	virtual ~CSkyBox();

	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext, shared_ptr<CCamera>pCamera);
};


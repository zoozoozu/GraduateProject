#pragma once
#include "Shader/Shader.h"
class CPlayerShader :
	public CDiffusedShader
{
public:
	CPlayerShader();
	virtual ~CPlayerShader();

	//virtual void CreateShader(ID3D11Device *pd3dDevice);
	virtual void BuildObjects(ID3D11Device *pd3dDevice);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext, CCamera *pCamera = NULL);

	CPlayer *GetPlayer(int nIndex = 0) {
		return((CPlayer *)m_ppObjects[nIndex]);
	}

};
#pragma once
#include "Shader/Shader.h"
class CSceneShader :
	public CDiffusedShader
{
public:
	CSceneShader(int nObjects);
	virtual ~CSceneShader();

	virtual void CreateShader(ID3D11Device *pd3dDevice);
	virtual void BuildObjects(ID3D11Device *pd3dDevice);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext, CCamera *pCamera = nullptr);
};


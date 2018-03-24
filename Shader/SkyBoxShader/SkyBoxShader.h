#pragma once
#include "Shader/Shader.h"
class CSkyBoxShader : public CTexturedShader
{
public:
	CSkyBoxShader(int nObjects);
	virtual ~CSkyBoxShader();

	virtual void BuildObjects(ID3D11Device *pd3dDevice);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext, CCamera *pCamera);
};



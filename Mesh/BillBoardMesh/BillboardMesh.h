#pragma once

#include "Mesh/Mesh.h"

class CBillboardMesh :
	public CMeshTexturedIlluminated
{
private:
	float					m_left				{ 0.0f };
	float					m_right				{ 0.0f };
	float					m_top				{ 0.0f };
	float					m_bottom			{ 0.0f };

public:
	CBillboardMesh(ID3D11Device *pd3dDevice, float posX = 0, float posY= 0, float fWidth = 2.0f, float fHeight = 2.0f);
	virtual ~CBillboardMesh();

	virtual void CreateRasterizerState(ID3D11Device *pd3dDevice);
	//virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);

};


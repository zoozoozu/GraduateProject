#pragma once
#include "Mesh/Mesh.h"
class CCubeMesh :
	public CMeshDiffused
{
public:
	CCubeMesh(ID3D11Device *pd3dDevice, float fWidth, float fHeight, float fDepth, XMFLOAT4 d3dxColor = XMFLOAT4(1.0f, 1.0f, 0.0f, 0.0f));
	virtual ~CCubeMesh();

protected:
	ID3D11Buffer					*m_pd3dColorBuffer;
};

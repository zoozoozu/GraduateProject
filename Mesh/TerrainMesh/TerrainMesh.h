#pragma once
#include "Mesh/Mesh.h"

class CTerrainMesh : public CMeshDetailTexturedIlluminated
{
protected:
	int							m_nWidth;
	int							m_nLength;
	XMFLOAT3					m_d3dxvScale;

public:
	CTerrainMesh(ID3D11Device *pd3dDevice, int xStart, int zStart, int nWidth, int nLength, XMFLOAT3 d3dxvScale = XMFLOAT3(1.0f, 1.0f, 1.0f), void *pContext = NULL);
	virtual ~CTerrainMesh();

	XMFLOAT3 GetScale() { return(m_d3dxvScale); }
	int GetWidth() { return(m_nWidth); }
	int GetLength() { return(m_nLength); }

	virtual float OnGetHeight(int x, int z, void *pContext);
	virtual void CreateRasterizerState(ID3D11Device *pd3dDevice);
};


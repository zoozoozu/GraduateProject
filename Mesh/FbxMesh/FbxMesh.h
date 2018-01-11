#pragma once
#include "Mesh/Mesh.h"

class CFbxMesh :
	public CMeshTexturedIlluminated
{
protected:
	XMFLOAT3		*m_pd3dxvPositions;
	XMFLOAT3		*m_pd3dxvNormals;
	XMFLOAT2		*m_pd3dxvTexCoords;

	float m_fFBXModelSize;		// ���� ������ (���� Animate���� �������ֱ� ����)

public:
	CFbxMesh(ID3D11Device *pd3dDevice);
	virtual ~CFbxMesh();
};


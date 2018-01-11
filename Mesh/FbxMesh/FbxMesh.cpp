#include "stdafx.h"
#include "Mesh/FbxMesh/FbxMesh.h"

CFbxMesh::CFbxMesh(ID3D11Device * pd3dDevice)
	:CMeshTexturedIlluminated(pd3dDevice)
{
	m_pd3dxvPositions = nullptr;
	m_pd3dxvNormals = nullptr;
	m_pd3dxvTexCoords = nullptr;

	m_fFBXModelSize = 0;
}

CFbxMesh::~CFbxMesh()
{
}

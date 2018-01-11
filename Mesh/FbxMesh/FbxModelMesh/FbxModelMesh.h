#pragma once
#include "Mesh/FbxMesh/FbxMesh.h"

class CFbxModelMesh
	: public CFbxMesh
{
private:

public:
	CFbxModelMesh(ID3D11Device *pd3dDevice, char *pszFileName, float fSize);
	~CFbxModelMesh();
};


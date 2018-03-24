#pragma once
#include "Shader/Shader.h"

class CHeightMapTerrain;

class CTerrainShader : public CDetailTexturedIlluminatedShader
{
public:
	CTerrainShader(int nObjects);
	virtual ~CTerrainShader();

	virtual void BuildObjects(ID3D11Device *pd3dDevice);

	CHeightMapTerrain *GetTerrain();
};


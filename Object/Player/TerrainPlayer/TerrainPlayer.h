#pragma once
#include "Object/Player/Player.h"

class CTerrainPlayer : public CPlayer
{
public:
	CTerrainPlayer(int nMeshes);
	virtual ~CTerrainPlayer();

	virtual void ChangeCamera(ID3D11Device *pd3dDevice, DWORD nNewCameraMode, float fTimeElapsed);
	
	virtual void OnPlayerUpdated(float fTimeElapsed);
	virtual void OnCameraUpdated(float fTimeElapsed);

};



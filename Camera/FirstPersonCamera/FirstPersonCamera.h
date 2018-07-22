#pragma once
#include "Camera/Camera.h"
class CFirstPersonCamera :
	public CCamera
{
public:
	CFirstPersonCamera(shared_ptr<CCamera>pCamera);
	virtual ~CFirstPersonCamera() { }

	virtual void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f);

};


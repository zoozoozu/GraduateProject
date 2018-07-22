#pragma once
#include "Camera/Camera.h"
class CThirdPersonCamera :
	public CCamera
{
public:
	CThirdPersonCamera(shared_ptr<CCamera>pCamera);
	virtual ~CThirdPersonCamera() { }

	virtual void Update(XMVECTOR& d3dxvLookAt, float fTimeScale);
	virtual void SetLookAt(XMVECTOR& vLookAt);

};


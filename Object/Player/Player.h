#pragma once
#include "Object/Object.h"
#include "Camera/Camera.h"

// ------------------------ 방향키 ------------------------------ //
#define DIR_FORWARD		0x01
#define DIR_BACKWARD	0x02
#define DIR_LEFT		0x04
#define DIR_RIGHT		0x08
#define DIR_UP			0x10
#define DIR_DOWN		0x20

class CPlayer : public CGameObject
{
protected:
	//플레이어의 위치 벡터, x-축(Right), y-축(Up), z-축(Look) 벡터이다.
	XMFLOAT3 m_d3dxvPosition;
	XMFLOAT3 m_d3dxvRight;
	XMFLOAT3 m_d3dxvUp;
	XMFLOAT3 m_d3dxvLook;

	//플레이어가 로컬 x-축(Right), y-축(Up), z-축(Look)으로 얼마만큼 회전했는가를 나타낸다.
	float m_fPitch;
	float m_fYaw;
	float m_fRoll;

	//플레이어의 이동 속도를 나타내는 벡터이다.
	XMFLOAT3 m_d3dxvVelocity;
	//플레이어에 작용하는 중력을 나타내는 벡터이다.
	XMFLOAT3 m_d3dxvGravity;
	//xz-평면에서 (한 프레임 동안) 플레이어의 이동 속력의 최대값을 나타낸다.
	float m_fMaxVelocityXZ;
	//y-축 방향으로 (한 프레임 동안) 플레이어의 이동 속력의 최대값을 나타낸다.
	float m_fMaxVelocityY;
	//플레이어에 작용하는 마찰력을 나타낸다.
	float m_fFriction;

	//플레이어의 위치가 바뀔 때마다 호출되는 OnPlayerUpdated() 함수에서 사용하는 데이터이다.
	LPVOID m_pPlayerUpdatedContext;
	//카메라의 위치가 바뀔 때마다 호출되는 OnCameraUpdated() 함수에서 사용하는 데이터이다.
	LPVOID m_pCameraUpdatedContext;

	shared_ptr<CCamera> m_pCamera;

public:
	XMFLOAT3 GetPosition() { return(m_d3dxvPosition); }
	XMFLOAT3 GetLookVector() { return(m_d3dxvLook); }
	XMFLOAT3 GetUpVector() { return(m_d3dxvUp); }
	XMFLOAT3 GetRightVector() { return(m_d3dxvRight); }

	XMVECTOR GetPositionXMV() {
		XMVECTOR xmvPosition = XMLoadFloat3(&m_d3dxvPosition);
		return xmvPosition;
	}
	XMVECTOR GetLookXMV() {
		XMVECTOR xmvLook = XMLoadFloat3(&m_d3dxvLook);
		return xmvLook;
	}
	XMVECTOR GetUpXMV() {
		XMVECTOR xmvUp = XMLoadFloat3(&m_d3dxvUp);
		return xmvUp;
	}
	XMVECTOR GetRightXMV() {
		XMVECTOR xmvRight = XMLoadFloat3(&m_d3dxvRight);
		return xmvRight;
	}

	void SetFriction(float fFriction) { m_fFriction = fFriction; }
	void SetGravity(const XMFLOAT3& d3dxvGravity) { m_d3dxvGravity = d3dxvGravity; }
	void SetMaxVelocityXZ(float fMaxVelocity) { m_fMaxVelocityXZ = fMaxVelocity; }
	void SetMaxVelocityY(float fMaxVelocity) { m_fMaxVelocityY = fMaxVelocity; }
	void SetVelocity(const XMFLOAT3& d3dxvVelocity) { m_d3dxvVelocity = d3dxvVelocity; }

	/*플레이어의 위치를 d3dxvPosition 위치로 설정한다. d3dxvPosition 벡터에서 현재 플레이어의 위치 벡터를 빼면 현재 플레이어의 위치에서 d3dxvPosition 방향으로의 방향 벡터가 된다. 현재 플레이어의 위치에서 이 방향 벡터 만큼 이동한다.*/
	void SetPosition(XMFLOAT3& d3dxvPosition) {
		d3dxvPosition.x -= m_d3dxvPosition.x;
		d3dxvPosition.y -= m_d3dxvPosition.y;
		d3dxvPosition.z -= m_d3dxvPosition.z;
		Move(XMLoadFloat3(&d3dxvPosition), false); 
	}

	const XMFLOAT3& GetVelocity() const { return(m_d3dxvVelocity); }
	float GetYaw() const { return(m_fYaw); }
	float GetPitch() const { return(m_fPitch); }
	float GetRoll() const { return(m_fRoll); }

	//플레이어를 이동하는 함수이다.
	void Move(DWORD nDirection, float fDistance, bool bVelocity = false);
	void Move(const XMVECTOR& d3dxvShift, bool bVelocity = false);
	void Move(float fxOffset = 0.0f, float fyOffset = 0.0f, float fzOffset = 0.0f);
	//플레이어를 회전하는 함수이다.
	void Rotate(float x, float y, float z);

	//플레이어의 위치와 회전 정보를 경과 시간에 따라 갱신하는 함수이다.
	void Update(float fTimeElapsed);

	//플레이어의 위치가 바뀔 때마다 호출되는 함수와 그 함수에서 사용하는 정보를 설정하는 함수이다.
	virtual void OnPlayerUpdated(float fTimeElapsed);
	void SetPlayerUpdatedContext(LPVOID pContext) { m_pPlayerUpdatedContext = pContext; }

	//카메라의 위치가 바뀔 때마다 호출되는 함수와 그 함수에서 사용하는 정보를 설정하는 함수이다.
	virtual void OnCameraUpdated(float fTimeElapsed);
	void SetCameraUpdatedContext(LPVOID pContext) { m_pCameraUpdatedContext = pContext; }

	//카메라를 변경할 때 호출되는 함수이다.
	shared_ptr<CCamera>OnChangeCamera(ID3D11Device *pd3dDevice, DWORD nNewCameraMode, DWORD nCurrentCameraMode);

	virtual void ChangeCamera(ID3D11Device *pd3dDevice, DWORD nNewCameraMode, float fTimeElapsed);
	//플레이어의 위치와 회전축으로부터 월드 변환 행렬을 생성하는 함수이다.
	virtual void OnPrepareRender();
	//플레이어의 카메라가 3인칭 카메라일 때 플레이어 메쉬를 렌더링한다.
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext, shared_ptr<CCamera> pCamera);

public:
	CPlayer(int nMeshes = 1);
	~CPlayer();

	// 플레이어의 현재 카메라를 설정하고 반환하는 멤버 함수를 선언한다.
	void SetCamera(shared_ptr<CCamera> pCamera) { m_pCamera = pCamera; }
	shared_ptr<CCamera> GetCamera() { return (m_pCamera); }

	// 플레이어의 상수 버퍼를 생성하고 갱신하는 멤버 함수를 선언한다.
	void CreateShaderVariables(ID3D11Device *pd3dDevice);
	void UpdateShaderVariables(ID3D11DeviceContext *pd3dDeviceContext);
};



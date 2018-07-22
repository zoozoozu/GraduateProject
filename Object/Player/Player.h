#pragma once
#include "Object/Object.h"
#include "Camera/Camera.h"

// ------------------------ ����Ű ------------------------------ //
#define DIR_FORWARD		0x01
#define DIR_BACKWARD	0x02
#define DIR_LEFT		0x04
#define DIR_RIGHT		0x08
#define DIR_UP			0x10
#define DIR_DOWN		0x20

class CPlayer : public CGameObject
{
protected:
	//�÷��̾��� ��ġ ����, x-��(Right), y-��(Up), z-��(Look) �����̴�.
	XMFLOAT3 m_d3dxvPosition;
	XMFLOAT3 m_d3dxvRight;
	XMFLOAT3 m_d3dxvUp;
	XMFLOAT3 m_d3dxvLook;

	//�÷��̾ ���� x-��(Right), y-��(Up), z-��(Look)���� �󸶸�ŭ ȸ���ߴ°��� ��Ÿ����.
	float m_fPitch;
	float m_fYaw;
	float m_fRoll;

	//�÷��̾��� �̵� �ӵ��� ��Ÿ���� �����̴�.
	XMFLOAT3 m_d3dxvVelocity;
	//�÷��̾ �ۿ��ϴ� �߷��� ��Ÿ���� �����̴�.
	XMFLOAT3 m_d3dxvGravity;
	//xz-��鿡�� (�� ������ ����) �÷��̾��� �̵� �ӷ��� �ִ밪�� ��Ÿ����.
	float m_fMaxVelocityXZ;
	//y-�� �������� (�� ������ ����) �÷��̾��� �̵� �ӷ��� �ִ밪�� ��Ÿ����.
	float m_fMaxVelocityY;
	//�÷��̾ �ۿ��ϴ� �������� ��Ÿ����.
	float m_fFriction;

	//�÷��̾��� ��ġ�� �ٲ� ������ ȣ��Ǵ� OnPlayerUpdated() �Լ����� ����ϴ� �������̴�.
	LPVOID m_pPlayerUpdatedContext;
	//ī�޶��� ��ġ�� �ٲ� ������ ȣ��Ǵ� OnCameraUpdated() �Լ����� ����ϴ� �������̴�.
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

	/*�÷��̾��� ��ġ�� d3dxvPosition ��ġ�� �����Ѵ�. d3dxvPosition ���Ϳ��� ���� �÷��̾��� ��ġ ���͸� ���� ���� �÷��̾��� ��ġ���� d3dxvPosition ���������� ���� ���Ͱ� �ȴ�. ���� �÷��̾��� ��ġ���� �� ���� ���� ��ŭ �̵��Ѵ�.*/
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

	//�÷��̾ �̵��ϴ� �Լ��̴�.
	void Move(DWORD nDirection, float fDistance, bool bVelocity = false);
	void Move(const XMVECTOR& d3dxvShift, bool bVelocity = false);
	void Move(float fxOffset = 0.0f, float fyOffset = 0.0f, float fzOffset = 0.0f);
	//�÷��̾ ȸ���ϴ� �Լ��̴�.
	void Rotate(float x, float y, float z);

	//�÷��̾��� ��ġ�� ȸ�� ������ ��� �ð��� ���� �����ϴ� �Լ��̴�.
	void Update(float fTimeElapsed);

	//�÷��̾��� ��ġ�� �ٲ� ������ ȣ��Ǵ� �Լ��� �� �Լ����� ����ϴ� ������ �����ϴ� �Լ��̴�.
	virtual void OnPlayerUpdated(float fTimeElapsed);
	void SetPlayerUpdatedContext(LPVOID pContext) { m_pPlayerUpdatedContext = pContext; }

	//ī�޶��� ��ġ�� �ٲ� ������ ȣ��Ǵ� �Լ��� �� �Լ����� ����ϴ� ������ �����ϴ� �Լ��̴�.
	virtual void OnCameraUpdated(float fTimeElapsed);
	void SetCameraUpdatedContext(LPVOID pContext) { m_pCameraUpdatedContext = pContext; }

	//ī�޶� ������ �� ȣ��Ǵ� �Լ��̴�.
	shared_ptr<CCamera>OnChangeCamera(ID3D11Device *pd3dDevice, DWORD nNewCameraMode, DWORD nCurrentCameraMode);

	virtual void ChangeCamera(ID3D11Device *pd3dDevice, DWORD nNewCameraMode, float fTimeElapsed);
	//�÷��̾��� ��ġ�� ȸ�������κ��� ���� ��ȯ ����� �����ϴ� �Լ��̴�.
	virtual void OnPrepareRender();
	//�÷��̾��� ī�޶� 3��Ī ī�޶��� �� �÷��̾� �޽��� �������Ѵ�.
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext, shared_ptr<CCamera> pCamera);

public:
	CPlayer(int nMeshes = 1);
	~CPlayer();

	// �÷��̾��� ���� ī�޶� �����ϰ� ��ȯ�ϴ� ��� �Լ��� �����Ѵ�.
	void SetCamera(shared_ptr<CCamera> pCamera) { m_pCamera = pCamera; }
	shared_ptr<CCamera> GetCamera() { return (m_pCamera); }

	// �÷��̾��� ��� ���۸� �����ϰ� �����ϴ� ��� �Լ��� �����Ѵ�.
	void CreateShaderVariables(ID3D11Device *pd3dDevice);
	void UpdateShaderVariables(ID3D11DeviceContext *pd3dDeviceContext);
};



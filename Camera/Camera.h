#pragma once
#include "Mesh/Mesh.h"

struct VS_CB_CAMERA
{
	XMFLOAT4X4 m_d3dxmtxView;
	XMFLOAT4X4 m_d3dxmtxProjection;
};

class CPlayer;

class CCamera
{
protected:
	//ī�޶��� ��ġ(������ǥ��) �����̴�.
	XMFLOAT3 m_d3dxvPosition;
	// ī�޶��� ���� x - ��(Right), y - ��(Up), z - ��(Look)�� ��Ÿ���� �����̴�.* /
	XMFLOAT3 m_d3dxvRight;
	XMFLOAT3 m_d3dxvUp;
	XMFLOAT3 m_d3dxvLook;

	//ī�޶� x-��, z-��, y-������ �󸶸�ŭ ȸ���ߴ� ���� ��Ÿ���� �����̴�.
	float m_fPitch;
	float m_fRoll;
	float m_fYaw;

	//ī�޶��� ����(1��Ī ī�޶�, �����̽�-�� ī�޶�, 3��Ī ī�޶�)�� ��Ÿ����.
	DWORD m_nMode;

	//�÷��̾�� ī�޶��� �������� ��Ÿ���� �����̴�. �ַ� 3��Ī ī�޶󿡼� ���ȴ�.
	XMFLOAT3 m_d3dxvOffset;
	//�÷��̾ ȸ���� �� �󸶸�ŭ�� �ð��� ������Ų �� ī�޶� ȸ����ų ���ΰ��� ��Ÿ����.
	float m_fTimeLag;

	// ī�޶� ��ȯ ��İ� ���� ��ȯ ����� ��Ÿ���� ��� ������ ����.
	XMFLOAT4X4 m_d3dxmtxView;
	XMFLOAT4X4 m_d3dxmtxProjection;

	// ��-��Ʈ�� ��Ÿ���� ��� ������ �����Ѵ�.
	D3D11_VIEWPORT m_d3dViewport;

	// ī�޶� ��ȯ ��İ� ���� ��ȯ ����� ���� ��� ���� �������̽� �����͸� �����Ѵ�.
	ID3D11Buffer *m_pd3dcbCamera;

	// ī�޶� ����� �÷��̾� ��ü�� ���� �����͸� �����Ѵ�.
	CPlayer *m_pPlayer;

	// ����ü
	XMFLOAT4 m_d3dxFrustumPlanes[6];

public:
	CCamera(CCamera *pCamera);
	virtual ~CCamera();

public:
	void SetMode(DWORD nMode) { m_nMode = nMode; }
	DWORD GetMode() { return(m_nMode); }
	CPlayer *GetPlayer() { return(m_pPlayer); }
	XMFLOAT4X4 GetViewMatrix() { return(m_d3dxmtxView); }
	XMFLOAT4X4 GetProjectionMatrix() { return(m_d3dxmtxProjection); }
	D3D11_VIEWPORT GetViewport() { return(m_d3dViewport); }
	void SetPlayer(CPlayer *pPlayer) { m_pPlayer = pPlayer; }

	void SetPosition(XMFLOAT3 d3dxvPosition) { m_d3dxvPosition = d3dxvPosition; }
	
	XMFLOAT3& GetPosition() { return(m_d3dxvPosition); }
	XMFLOAT3& GetRightVector() { return(m_d3dxvRight); }
	XMFLOAT3& GetUpVector() { return(m_d3dxvUp); }
	XMFLOAT3& GetLookVector() { return(m_d3dxvLook); }

	float& GetPitch() { return(m_fPitch); }
	float& GetRoll() { return(m_fRoll); }
	float& GetYaw() { return(m_fYaw); }

	void SetOffset(XMFLOAT3 d3dxvOffset) { 
		m_d3dxvOffset = d3dxvOffset; 
		m_d3dxvPosition.x += d3dxvOffset.x;
		m_d3dxvPosition.y += d3dxvOffset.y;
		m_d3dxvPosition.z += d3dxvOffset.z;
	}
	XMFLOAT3& GetOffset() { return(m_d3dxvOffset); }

	void SetTimeLag(float fTimeLag) { m_fTimeLag = fTimeLag; }
	float GetTimeLag() { return(m_fTimeLag); }

	//ī�޶� d3dxvShift ��ŭ �̵��ϴ� �����Լ��̴�.
	virtual void Move(const XMVECTOR& d3dxvShift) {
		XMVECTOR xmvPosition = XMLoadFloat3(&m_d3dxvPosition);
		xmvPosition += d3dxvShift;
		XMStoreFloat3(&m_d3dxvPosition, xmvPosition);
	}
	//ī�޶� x-��, y-��, z-������ ȸ���ϴ� �����Լ��̴�.
	virtual void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f) { }
	//ī�޶��� �̵�, ȸ���� ���� ī�޶��� ������ �����ϴ� �����Լ��̴�.
	virtual void Update(XMVECTOR& d3dxvLookAt, float fTimeElapsed) { }
	/*3��Ī ī�޶󿡼� ī�޶� �ٶ󺸴� ������ �����ϴ� �����Լ��̴�. �Ϲ������� �÷��̾ �ٶ󺸵��� �����Ѵ�.*/
	virtual void SetLookAt(XMFLOAT3& vLookAt) { }

	XMFLOAT4X4& GetViewMatrixXMFLOAT4X4() { return (m_d3dxmtxView); }
	XMFLOAT4X4& GetProjectionMatrixXMFLOAT4X4() { return (m_d3dxmtxProjection); }
	ID3D11Buffer *GetCameraConstantBuffer() { return(m_pd3dcbCamera); }

	// ��-��Ʈ�� �����ϴ� ��� �Լ��� �����Ѵ�.
	void SetViewport(ID3D11DeviceContext *pd3dDeviceContext,
		DWORD xTopLeft, DWORD yTopLeft, DWORD nWidth, DWORD nHeight,
		float fMinZ = 0.0f, float fMaxZ = 1.0f);

	// ī�޶� ��ȯ ��İ� ���� ��ȯ ����� �����ϴ� ��� �Լ��� �����Ѵ�.
	void GenerateViewMatrix();
	/*ī�޶� ������ ȸ���� �ϰ� �Ǹ� ������ �Ǽ������� ����Ȯ�� ������ 
	ī�޶��� ���� x-��(Right), y-��(Up), z-��(LookAt)�� ���� �������� ���� �� �ִ�. 
	ī�޶��� ���� x-��(Right), y-��(Up), z-��(LookAt)�� ���� �����ϵ��� ������ش�.*/
	void RegenerateViewMatrix();

	void GenerateProjectionMatrix(float fNearPlaneDistance, float
		fFarPlaneDistance, float fAspectRatio, float fFOVAngle);

	// ��� ���۸� �����ϰ� ������ �����ϴ� ��� �Լ��� �����Ѵ�.
	void CreateShaderVariables(ID3D11Device *pd3dDevice);
	void UpdateShaderVariables(ID3D11DeviceContext *pd3dDeviceContext);

	// ����ü
	//����ü�� 6�� ����� ����Ѵ�.
	void CalculateFrustumPlanes();
	//�ٿ�� �ڽ��� ����ü�� ������ ���Եǰų� �Ϻζ� ���ԵǴ� ���� �˻��Ѵ�.
	bool IsInFrustum(XMFLOAT3& d3dxvMinimum, XMFLOAT3& d3dxvMaximum);
	bool IsInFrustum(AABB *pAABB);

};


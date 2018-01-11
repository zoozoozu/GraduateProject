#include "stdafx.h"
#include "Object/Player/Player.h"
#include "Camera/ThirdPersonCamera/ThirdPersonCamera.h"


CThirdPersonCamera::CThirdPersonCamera(CCamera *pCamera)
	:CCamera(pCamera)
{
	m_nMode = THIRD_PERSON_CAMERA;
	if (pCamera)
	{
		if (pCamera->GetMode() == SPACESHIP_CAMERA)
		{
			m_d3dxvUp = XMFLOAT3(0.0f, 1.0f, 0.0f);
			m_d3dxvRight.y = 0.0f;
			m_d3dxvLook.y = 0.0f;
			XMStoreFloat3(&m_d3dxvRight, XMVector3Normalize(XMLoadFloat3(&m_d3dxvRight)));
			XMStoreFloat3(&m_d3dxvLook, XMVector3Normalize(XMLoadFloat3(&m_d3dxvLook)));
		}
	}
}

void CThirdPersonCamera::Update(XMVECTOR& d3dxvLookAt, float fTimeScale)
{
	// 플레이어의 회전에 따라 3인칭 카메라도 회전해야 한다.
	if (m_pPlayer)
	{
		XMMATRIX mtxRotate;
		mtxRotate = XMMatrixIdentity();

		XMVECTOR d3dxvRight = m_pPlayer->GetRightXMV();
		XMVECTOR d3dxvUp = m_pPlayer->GetUpXMV();
		XMVECTOR d3dxvLook = m_pPlayer->GetLookXMV();

		XMFLOAT3 xmfRight;
		XMStoreFloat3(&xmfRight, d3dxvRight);
		XMFLOAT3 xmfUp;
		XMStoreFloat3(&xmfUp, d3dxvUp);
		XMFLOAT3 xmfLook;
		XMStoreFloat3(&xmfLook, d3dxvLook);

		XMFLOAT4X4 xmf4x4Rotate;
		XMStoreFloat4x4(&xmf4x4Rotate, mtxRotate);
		// 플레이어의 로컬 x-축, y-축, z-축 벡터로부터 회전 행렬을 생성한다.
		xmf4x4Rotate._11 = xmfRight.x; xmf4x4Rotate._21 = xmfUp.x; xmf4x4Rotate._31 = xmfLook.x;
		xmf4x4Rotate._12 = xmfRight.y; xmf4x4Rotate._22 = xmfUp.y; xmf4x4Rotate._32 = xmfLook.y;
		xmf4x4Rotate._13 = xmfRight.z; xmf4x4Rotate._23 = xmfUp.z; xmf4x4Rotate._33 = xmfLook.z;
		
		mtxRotate = XMLoadFloat4x4(&xmf4x4Rotate);

		XMVECTOR d3dxvOffset;
		d3dxvOffset = XMVector3TransformCoord(XMLoadFloat3(&m_d3dxvOffset), mtxRotate);

		// 회전한 카메라의 위치는 플레이어의 위치에 회전한 카메라 오프셋 벡터를 더한 것이다.
		XMVECTOR d3dxvPosition = m_pPlayer->GetPositionXMV() + d3dxvOffset;
		// 현재의 카메라의 위치에서 회전한 카메라의 위치까지의 벡터이다.
		XMVECTOR d3dxvDirection = d3dxvPosition - XMLoadFloat3(&m_d3dxvPosition);

		XMVECTOR fLength = XMVector3Length(d3dxvDirection);

		XMFLOAT3 xmLength;
		XMStoreFloat3(&xmLength, fLength);

		d3dxvDirection = XMVector3Normalize(d3dxvDirection);

		// 3인칭 카메라의 래그는 플레이어가 회전하더라도 카메라가 동시에 따라서 회전하지 않고
		// 약간의 시차를 두고 회전하는 효과를 구현하기 위한 것이다.
		// m_fTimeLag가 1보다 크면 fTimeLagScale이 작아지고 실제 회전이 적게 일어날 것이다.
		float fTimeLagScale = (m_fTimeLag) ? fTimeScale * (1.0f / m_fTimeLag) : 1.0f;

		float fDistance = xmLength.x * fTimeLagScale;
		if (fDistance > xmLength.x) fDistance = xmLength.x;
		if (xmLength.x < 0.01f) fDistance = xmLength.x;

		if (fDistance > 0)
		{
			XMVECTOR xmvecPosition = XMLoadFloat3(&m_d3dxvPosition);
			xmvecPosition += d3dxvDirection * fDistance;
			XMStoreFloat3(&m_d3dxvPosition, xmvecPosition);
			SetLookAt(d3dxvLookAt);
		}
	}
}

void CThirdPersonCamera::SetLookAt(XMVECTOR& vLookAt)
{
	XMMATRIX mtxLookAt;
	mtxLookAt = XMMatrixLookAtLH(XMLoadFloat3(&m_d3dxvPosition), vLookAt, m_pPlayer->GetUpXMV());

	XMFLOAT4X4 xmf4x4LookAt;
	XMStoreFloat4x4(&xmf4x4LookAt, mtxLookAt);

	m_d3dxvRight = XMFLOAT3(xmf4x4LookAt._11, xmf4x4LookAt._21, xmf4x4LookAt._31);
	m_d3dxvUp = XMFLOAT3(xmf4x4LookAt._12, xmf4x4LookAt._22, xmf4x4LookAt._32);
	m_d3dxvLook = XMFLOAT3(xmf4x4LookAt._13, xmf4x4LookAt._23, xmf4x4LookAt._33);

	mtxLookAt = XMLoadFloat4x4(&xmf4x4LookAt);
}



#include "stdafx.h"
#include "Object/Player/Player.h"
#include "Camera/ThirdPersonCamera/ThirdPersonCamera.h"


CThirdPersonCamera::CThirdPersonCamera(shared_ptr<CCamera>pCamera)
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
	// �÷��̾��� ȸ���� ���� 3��Ī ī�޶� ȸ���ؾ� �Ѵ�.
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
		// �÷��̾��� ���� x-��, y-��, z-�� ���ͷκ��� ȸ�� ����� �����Ѵ�.
		xmf4x4Rotate._11 = xmfRight.x; xmf4x4Rotate._21 = xmfUp.x; xmf4x4Rotate._31 = xmfLook.x;
		xmf4x4Rotate._12 = xmfRight.y; xmf4x4Rotate._22 = xmfUp.y; xmf4x4Rotate._32 = xmfLook.y;
		xmf4x4Rotate._13 = xmfRight.z; xmf4x4Rotate._23 = xmfUp.z; xmf4x4Rotate._33 = xmfLook.z;
		
		mtxRotate = XMLoadFloat4x4(&xmf4x4Rotate);

		XMVECTOR d3dxvOffset;
		d3dxvOffset = XMVector3TransformCoord(XMLoadFloat3(&m_d3dxvOffset), mtxRotate);

		// ȸ���� ī�޶��� ��ġ�� �÷��̾��� ��ġ�� ȸ���� ī�޶� ������ ���͸� ���� ���̴�.
		XMVECTOR d3dxvPosition = m_pPlayer->GetPositionXMV() + d3dxvOffset;
		// ������ ī�޶��� ��ġ���� ȸ���� ī�޶��� ��ġ������ �����̴�.
		XMVECTOR d3dxvDirection = d3dxvPosition - XMLoadFloat3(&m_d3dxvPosition);

		XMVECTOR fLength = XMVector3Length(d3dxvDirection);

		XMFLOAT3 xmLength;
		XMStoreFloat3(&xmLength, fLength);

		d3dxvDirection = XMVector3Normalize(d3dxvDirection);

		// 3��Ī ī�޶��� ���״� �÷��̾ ȸ���ϴ��� ī�޶� ���ÿ� ���� ȸ������ �ʰ�
		// �ణ�� ������ �ΰ� ȸ���ϴ� ȿ���� �����ϱ� ���� ���̴�.
		// m_fTimeLag�� 1���� ũ�� fTimeLagScale�� �۾����� ���� ȸ���� ���� �Ͼ ���̴�.
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



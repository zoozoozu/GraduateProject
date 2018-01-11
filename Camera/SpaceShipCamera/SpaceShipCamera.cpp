#include "stdafx.h"
#include "Object/Player/Player.h"
#include "Camera/SpaceShipCamera/SpaceShipCamera.h"


CSpaceShipCamera::CSpaceShipCamera(CCamera *pCamera) : CCamera(pCamera)
{
	m_nMode = SPACESHIP_CAMERA;
}

void CSpaceShipCamera::Rotate(float fPitch, float fYaw, float fRoll)
{
	XMMATRIX mtxRotate;

	if (m_pPlayer && (fPitch != 0.0f))
	{
		// �÷��̾��� ���� x-�࿡ ���� x ������ ȸ�� ����� ����Ѵ�.
		mtxRotate = XMMatrixRotationAxis(m_pPlayer->GetRightXMV(), XMConvertToRadians(fPitch));

		// ī�޶��� ���� x-��, y-��, z-���� ȸ���Ѵ�.
		XMStoreFloat3(&m_d3dxvRight, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvRight), mtxRotate));
		XMStoreFloat3(&m_d3dxvUp, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvUp), mtxRotate));
		XMStoreFloat3(&m_d3dxvLook, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvLook), mtxRotate));

		// ī�޶��� ��ġ ���Ϳ��� �÷��̾��� ��ġ ���͸� ����.
		// ����� �÷��̾� ��ġ�� �������� �� ī�޶��� ��ġ �����̴�.
		XMVECTOR xmvecPosition = XMLoadFloat3(&m_d3dxvPosition);
		xmvecPosition -= m_pPlayer->GetPositionXMV();
		XMStoreFloat3(&m_d3dxvPosition, xmvecPosition);

		// �÷��̾��� ��ġ�� �߽����� ī�޶��� ��ġ ����(�÷��̾ �������� ��)��
		// ȸ���Ѵ�.
		XMStoreFloat3(&m_d3dxvPosition, XMVector3TransformCoord(XMLoadFloat3(&m_d3dxvPosition), mtxRotate));

		// ȸ����Ų ī�޶��� ��ġ ���Ϳ� �÷��̾��� ��ġ�� ���Ѵ�.
		xmvecPosition += m_pPlayer->GetPositionXMV();
		XMStoreFloat3(&m_d3dxvPosition, xmvecPosition);
	}

	if (m_pPlayer && (fYaw != 0.0f))
	{
		// �÷��̾��� ���� x-�࿡ ���� x ������ ȸ�� ����� ����Ѵ�.
		mtxRotate = XMMatrixRotationAxis(m_pPlayer->GetUpXMV(), XMConvertToRadians(fYaw));

		// ī�޶��� ���� x-��, y-��, z-���� ȸ���Ѵ�.
		XMStoreFloat3(&m_d3dxvRight, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvRight), mtxRotate));
		XMStoreFloat3(&m_d3dxvUp, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvUp), mtxRotate));
		XMStoreFloat3(&m_d3dxvLook, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvLook), mtxRotate));

		// ī�޶��� ��ġ ���Ϳ��� �÷��̾��� ��ġ ���͸� ����.
		// ����� �÷��̾� ��ġ�� �������� �� ī�޶��� ��ġ �����̴�.
		XMVECTOR xmvecPosition = XMLoadFloat3(&m_d3dxvPosition);
		xmvecPosition -= m_pPlayer->GetPositionXMV();
		XMStoreFloat3(&m_d3dxvPosition, xmvecPosition);

		// �÷��̾��� ��ġ�� �߽����� ī�޶��� ��ġ ����(�÷��̾ �������� ��)��
		// ȸ���Ѵ�.
		XMStoreFloat3(&m_d3dxvPosition, XMVector3TransformCoord(XMLoadFloat3(&m_d3dxvPosition), mtxRotate));

		// ȸ����Ų ī�޶��� ��ġ ���Ϳ� �÷��̾��� ��ġ�� ���Ѵ�.
		xmvecPosition += m_pPlayer->GetPositionXMV();
		XMStoreFloat3(&m_d3dxvPosition, xmvecPosition);
	}

	if (m_pPlayer && (fRoll != 0.0f))
	{
		// �÷��̾��� ���� x-�࿡ ���� x ������ ȸ�� ����� ����Ѵ�.
		mtxRotate = XMMatrixRotationAxis(m_pPlayer->GetLookXMV(), XMConvertToRadians(fRoll));

		// ī�޶��� ���� x-��, y-��, z-���� ȸ���Ѵ�.
		XMStoreFloat3(&m_d3dxvRight, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvRight), mtxRotate));
		XMStoreFloat3(&m_d3dxvUp, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvUp), mtxRotate));
		XMStoreFloat3(&m_d3dxvLook, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvLook), mtxRotate));

		// ī�޶��� ��ġ ���Ϳ��� �÷��̾��� ��ġ ���͸� ����.
		// ����� �÷��̾� ��ġ�� �������� �� ī�޶��� ��ġ �����̴�.
		XMVECTOR xmvecPosition = XMLoadFloat3(&m_d3dxvPosition);
		xmvecPosition -= m_pPlayer->GetPositionXMV();
		XMStoreFloat3(&m_d3dxvPosition, xmvecPosition);

		// �÷��̾��� ��ġ�� �߽����� ī�޶��� ��ġ ����(�÷��̾ �������� ��)��
		// ȸ���Ѵ�.
		XMStoreFloat3(&m_d3dxvPosition, XMVector3TransformCoord(XMLoadFloat3(&m_d3dxvPosition), mtxRotate));

		// ȸ����Ų ī�޶��� ��ġ ���Ϳ� �÷��̾��� ��ġ�� ���Ѵ�.
		xmvecPosition += m_pPlayer->GetPositionXMV();
		XMStoreFloat3(&m_d3dxvPosition, xmvecPosition);
	}
}


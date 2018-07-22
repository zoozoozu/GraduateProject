#include "stdafx.h"
#include "Object/Player/Player.h"
#include "Camera/FirstPersonCamera/FirstPersonCamera.h"


CFirstPersonCamera::CFirstPersonCamera(shared_ptr<CCamera>pCamera)
	:CCamera(pCamera)
{
	m_nMode = FIRST_PERSON_CAMERA;
	if (pCamera)
	{
		// 1��Ī ī�޶�� �����ϱ� ������ ī�޶� �����̽�-�� ī�޶��̸�
		// ī�޶��� Up ���͸� ������ǥ�� y-���� �ǵ��� �Ѵ�.
		// �̰��� �����̽�-�� ī�޶��� ���� y-�� ���Ͱ� � �����̵���
		// 1��Ī ī�޶�(��κ� ����� ���)�� ���� y-�� ���Ͱ� ������ǥ�� 
		// y-���� �ǵ��� ��, �ȹٷ� ���ִ� ���·� �����Ѵٴ� �ǹ��̴�.
		// �׸��� ���� x-�� ���Ϳ� ���� z-�� ������ y-��ǥ�� 0.0f�� �ǵ��� �Ѵ�.
		// �̰��� <�׸�8>�� ���� ���� x-�� ���Ϳ� ���� z-�� ���͸� xz-���(����)����
		// �����ϴ� ���� �ǹ��Ѵ�.
		// ��, 1��Ī ī�޶��� ���� x-�� ���Ϳ� ���� z-�� ���ʹ� xz-��鿡 �����ϴ�.
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

void CFirstPersonCamera::Rotate(float fPitch, float fYaw, float fRoll)
{
	XMMATRIX mtxRotate;

	if (fPitch != 0.0f)
	{
		// ī�޶��� ���� x-���� �������� ȸ���ϴ� ����� �����Ѵ�.
		// ���� �����̴� �����̴�.
		mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_d3dxvRight), XMConvertToRadians(fPitch));
		// ī�޶��� ���� x-��, y-��, z-���� ȸ���Ѵ�.
		XMStoreFloat3(&m_d3dxvRight, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvRight), mtxRotate));
		XMStoreFloat3(&m_d3dxvUp, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvUp), mtxRotate));
		XMStoreFloat3(&m_d3dxvLook, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvLook), mtxRotate));
	}

	if (m_pPlayer && (fYaw != 0.0f))
	{
		// �÷��̾��� ���� y-���� �������� ȸ���ϴ� ����� �����Ѵ�.
		mtxRotate = XMMatrixRotationAxis(m_pPlayer->GetUpXMV(), XMConvertToRadians(fYaw));
		// ī�޶��� ���� x-��, y-��, z-���� ȸ���Ѵ�.
		XMStoreFloat3(&m_d3dxvRight, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvRight), mtxRotate));
		XMStoreFloat3(&m_d3dxvUp, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvUp), mtxRotate));
		XMStoreFloat3(&m_d3dxvLook, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvLook), mtxRotate));
	}

	if (m_pPlayer && (fRoll != 0.0f))
	{
		// �÷��̾��� ���� z-���� �������� ȸ���ϴ� ����� �����Ѵ�.
		mtxRotate = XMMatrixRotationAxis(m_pPlayer->GetLookXMV(), XMConvertToRadians(fRoll));

		// ī�޶��� ��ġ ���͸� �÷��̾� ��ǥ��� ǥ���Ѵ�. (������ ����)
		XMVECTOR xmvecPosition = XMLoadFloat3(&m_d3dxvPosition);
		xmvecPosition -= m_pPlayer->GetPositionXMV();
		XMStoreFloat3(&m_d3dxvPosition, xmvecPosition);

		// ������ ���͸� ȸ���Ѵ�.
		XMStoreFloat3(&m_d3dxvPosition, XMVector3TransformCoord(XMLoadFloat3(&m_d3dxvPosition), mtxRotate));

		// ȸ���� ī�޶��� ��ġ�� ���� ��ǥ��� ǥ���Ѵ�.
		xmvecPosition += m_pPlayer->GetPositionXMV();
		XMStoreFloat3(&m_d3dxvPosition, xmvecPosition);

		// ī�޶��� ���� x-��, y-��, z-���� ȸ���Ѵ�.
		XMStoreFloat3(&m_d3dxvRight, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvRight), mtxRotate));
		XMStoreFloat3(&m_d3dxvUp, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvUp), mtxRotate));
		XMStoreFloat3(&m_d3dxvLook, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvLook), mtxRotate));
	}
}




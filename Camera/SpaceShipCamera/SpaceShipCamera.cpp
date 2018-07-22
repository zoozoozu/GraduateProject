#include "stdafx.h"
#include "Object/Player/Player.h"
#include "Camera/SpaceShipCamera/SpaceShipCamera.h"


CSpaceShipCamera::CSpaceShipCamera(shared_ptr<CCamera>pCamera) : CCamera(pCamera)
{
	m_nMode = SPACESHIP_CAMERA;
}

void CSpaceShipCamera::Rotate(float fPitch, float fYaw, float fRoll)
{
	XMMATRIX mtxRotate;

	if (m_pPlayer && (fPitch != 0.0f))
	{
		// 플레이어의 로컬 x-축에 대한 x 각도의 회전 행렬을 계산한다.
		mtxRotate = XMMatrixRotationAxis(m_pPlayer->GetRightXMV(), XMConvertToRadians(fPitch));

		// 카메라의 로컬 x-축, y-축, z-축을 회전한다.
		XMStoreFloat3(&m_d3dxvRight, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvRight), mtxRotate));
		XMStoreFloat3(&m_d3dxvUp, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvUp), mtxRotate));
		XMStoreFloat3(&m_d3dxvLook, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvLook), mtxRotate));

		// 카메라의 위치 벡터에서 플레이어의 위치 벡터를 뺀다.
		// 결과는 플레이어 위치를 기준으로 한 카메라의 위치 벡터이다.
		XMVECTOR xmvecPosition = XMLoadFloat3(&m_d3dxvPosition);
		xmvecPosition -= m_pPlayer->GetPositionXMV();
		XMStoreFloat3(&m_d3dxvPosition, xmvecPosition);

		// 플레이어의 위치를 중심으로 카메라의 위치 벡터(플레이어를 기준으로 한)를
		// 회전한다.
		XMStoreFloat3(&m_d3dxvPosition, XMVector3TransformCoord(XMLoadFloat3(&m_d3dxvPosition), mtxRotate));

		// 회전시킨 카메라의 위치 벡터에 플레이어의 위치를 더한다.
		xmvecPosition += m_pPlayer->GetPositionXMV();
		XMStoreFloat3(&m_d3dxvPosition, xmvecPosition);
	}

	if (m_pPlayer && (fYaw != 0.0f))
	{
		// 플레이어의 로컬 x-축에 대한 x 각도의 회전 행렬을 계산한다.
		mtxRotate = XMMatrixRotationAxis(m_pPlayer->GetUpXMV(), XMConvertToRadians(fYaw));

		// 카메라의 로컬 x-축, y-축, z-축을 회전한다.
		XMStoreFloat3(&m_d3dxvRight, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvRight), mtxRotate));
		XMStoreFloat3(&m_d3dxvUp, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvUp), mtxRotate));
		XMStoreFloat3(&m_d3dxvLook, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvLook), mtxRotate));

		// 카메라의 위치 벡터에서 플레이어의 위치 벡터를 뺀다.
		// 결과는 플레이어 위치를 기준으로 한 카메라의 위치 벡터이다.
		XMVECTOR xmvecPosition = XMLoadFloat3(&m_d3dxvPosition);
		xmvecPosition -= m_pPlayer->GetPositionXMV();
		XMStoreFloat3(&m_d3dxvPosition, xmvecPosition);

		// 플레이어의 위치를 중심으로 카메라의 위치 벡터(플레이어를 기준으로 한)를
		// 회전한다.
		XMStoreFloat3(&m_d3dxvPosition, XMVector3TransformCoord(XMLoadFloat3(&m_d3dxvPosition), mtxRotate));

		// 회전시킨 카메라의 위치 벡터에 플레이어의 위치를 더한다.
		xmvecPosition += m_pPlayer->GetPositionXMV();
		XMStoreFloat3(&m_d3dxvPosition, xmvecPosition);
	}

	if (m_pPlayer && (fRoll != 0.0f))
	{
		// 플레이어의 로컬 x-축에 대한 x 각도의 회전 행렬을 계산한다.
		mtxRotate = XMMatrixRotationAxis(m_pPlayer->GetLookXMV(), XMConvertToRadians(fRoll));

		// 카메라의 로컬 x-축, y-축, z-축을 회전한다.
		XMStoreFloat3(&m_d3dxvRight, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvRight), mtxRotate));
		XMStoreFloat3(&m_d3dxvUp, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvUp), mtxRotate));
		XMStoreFloat3(&m_d3dxvLook, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvLook), mtxRotate));

		// 카메라의 위치 벡터에서 플레이어의 위치 벡터를 뺀다.
		// 결과는 플레이어 위치를 기준으로 한 카메라의 위치 벡터이다.
		XMVECTOR xmvecPosition = XMLoadFloat3(&m_d3dxvPosition);
		xmvecPosition -= m_pPlayer->GetPositionXMV();
		XMStoreFloat3(&m_d3dxvPosition, xmvecPosition);

		// 플레이어의 위치를 중심으로 카메라의 위치 벡터(플레이어를 기준으로 한)를
		// 회전한다.
		XMStoreFloat3(&m_d3dxvPosition, XMVector3TransformCoord(XMLoadFloat3(&m_d3dxvPosition), mtxRotate));

		// 회전시킨 카메라의 위치 벡터에 플레이어의 위치를 더한다.
		xmvecPosition += m_pPlayer->GetPositionXMV();
		XMStoreFloat3(&m_d3dxvPosition, xmvecPosition);
	}
}


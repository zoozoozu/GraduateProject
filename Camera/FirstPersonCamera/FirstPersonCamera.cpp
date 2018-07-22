#include "stdafx.h"
#include "Object/Player/Player.h"
#include "Camera/FirstPersonCamera/FirstPersonCamera.h"


CFirstPersonCamera::CFirstPersonCamera(shared_ptr<CCamera>pCamera)
	:CCamera(pCamera)
{
	m_nMode = FIRST_PERSON_CAMERA;
	if (pCamera)
	{
		// 1인칭 카메라로 변경하기 이전의 카메라가 스페이스-쉽 카메라이면
		// 카메라의 Up 벡터를 월드좌표의 y-축이 되도록 한다.
		// 이것은 스페이스-쉽 카메라의 로컬 y-축 벡터가 어떤 방향이든지
		// 1인칭 카메라(대부분 사람인 경우)의 로컬 y-축 벡터가 월드좌표의 
		// y-축이 되도록 즉, 똑바로 서있는 형태로 설정한다는 의미이다.
		// 그리고 로컬 x-축 벡터와 로컬 z-축 벡터의 y-좌표가 0.0f가 되도록 한다.
		// 이것은 <그림8>과 같이 로컬 x-축 벡터와 로컬 z-축 벡터를 xz-평면(지면)으로
		// 투영하는 것을 의미한다.
		// 즉, 1인칭 카메라의 로컬 x-축 벡터와 로컬 z-축 벡터는 xz-평면에 평행하다.
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
		// 카메라의 로컬 x-축을 기준으로 회전하는 행렬을 생성한다.
		// 고개를 끄덕이는 동작이다.
		mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_d3dxvRight), XMConvertToRadians(fPitch));
		// 카메라의 로컬 x-축, y-축, z-축을 회전한다.
		XMStoreFloat3(&m_d3dxvRight, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvRight), mtxRotate));
		XMStoreFloat3(&m_d3dxvUp, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvUp), mtxRotate));
		XMStoreFloat3(&m_d3dxvLook, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvLook), mtxRotate));
	}

	if (m_pPlayer && (fYaw != 0.0f))
	{
		// 플레이어의 로컬 y-축을 기준으로 회전하는 행렬을 생성한다.
		mtxRotate = XMMatrixRotationAxis(m_pPlayer->GetUpXMV(), XMConvertToRadians(fYaw));
		// 카메라의 로컬 x-축, y-축, z-축을 회전한다.
		XMStoreFloat3(&m_d3dxvRight, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvRight), mtxRotate));
		XMStoreFloat3(&m_d3dxvUp, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvUp), mtxRotate));
		XMStoreFloat3(&m_d3dxvLook, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvLook), mtxRotate));
	}

	if (m_pPlayer && (fRoll != 0.0f))
	{
		// 플레이어의 로컬 z-축을 기준으로 회전하는 행렬을 생성한다.
		mtxRotate = XMMatrixRotationAxis(m_pPlayer->GetLookXMV(), XMConvertToRadians(fRoll));

		// 카메라의 위치 벡터를 플레이어 좌표계로 표현한다. (오프셋 벡터)
		XMVECTOR xmvecPosition = XMLoadFloat3(&m_d3dxvPosition);
		xmvecPosition -= m_pPlayer->GetPositionXMV();
		XMStoreFloat3(&m_d3dxvPosition, xmvecPosition);

		// 오프셋 벡터를 회전한다.
		XMStoreFloat3(&m_d3dxvPosition, XMVector3TransformCoord(XMLoadFloat3(&m_d3dxvPosition), mtxRotate));

		// 회전한 카메라의 위치를 월드 좌표계로 표현한다.
		xmvecPosition += m_pPlayer->GetPositionXMV();
		XMStoreFloat3(&m_d3dxvPosition, xmvecPosition);

		// 카메라의 로컬 x-축, y-축, z-축을 회전한다.
		XMStoreFloat3(&m_d3dxvRight, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvRight), mtxRotate));
		XMStoreFloat3(&m_d3dxvUp, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvUp), mtxRotate));
		XMStoreFloat3(&m_d3dxvLook, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvLook), mtxRotate));
	}
}




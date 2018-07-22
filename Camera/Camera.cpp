#include "stdafx.h"
#include "Object/Player/Player.h"
#include "Camera/Camera.h"

CCamera::CCamera(shared_ptr<CCamera>pCamera)
{
	if (pCamera)
	{
		//ī�޶� �̹� ������ ���� ī�޶��� ������ ���ο� ī�޶� �����Ѵ�. 
		m_d3dxvPosition = pCamera->GetPosition();
		m_d3dxvRight = pCamera->GetRightVector();
		m_d3dxvLook = pCamera->GetLookVector();
		m_d3dxvUp = pCamera->GetUpVector();
		m_fPitch = pCamera->GetPitch();
		m_fRoll = pCamera->GetRoll();
		m_fYaw = pCamera->GetYaw();
		m_d3dxmtxView = pCamera->GetViewMatrix();
		m_d3dxmtxProjection = pCamera->GetProjectionMatrix();
		m_d3dViewport = pCamera->GetViewport();
		m_d3dxvOffset = pCamera->GetOffset();
		m_fTimeLag = pCamera->GetTimeLag();
		m_pPlayer = pCamera->GetPlayer();
		m_pd3dcbCamera = pCamera->GetCameraConstantBuffer();
		if (m_pd3dcbCamera) m_pd3dcbCamera->AddRef();
	}
	else
	{
		//ī�޶� ������ �⺻ ������ �����Ѵ�. 
		m_d3dxvPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_d3dxvRight = XMFLOAT3(1.0f, 0.0f, 0.0f);
		m_d3dxvUp = XMFLOAT3(0.0f, 1.0f, 0.0f);
		m_d3dxvLook = XMFLOAT3(0.0f, 0.0f, 1.0f);
		m_fPitch = 0.0f;
		m_fRoll = 0.0f;
		m_fYaw = 0.0f;
		m_fTimeLag = 0.0f;
		m_d3dxvOffset = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_nMode = 0x00;
		m_pPlayer = NULL;
		XMStoreFloat4x4(&m_d3dxmtxView, XMMatrixIdentity());
		XMStoreFloat4x4(&m_d3dxmtxProjection, XMMatrixIdentity());
		m_pd3dcbCamera = NULL;
	}
}

CCamera::~CCamera()
{
	if (m_pd3dcbCamera)
		m_pd3dcbCamera->Release();
}

void CCamera::SetViewport(ID3D11DeviceContext * pd3dDeviceContext, DWORD xTopLeft, DWORD yTopLeft, DWORD nWidth, DWORD nHeight, float fMinZ, float fMaxZ)
{
	m_d3dViewport.TopLeftX = float(xTopLeft);
	m_d3dViewport.TopLeftY = float(yTopLeft);
	m_d3dViewport.Width = float(nWidth);
	m_d3dViewport.Height = float(nHeight);
	m_d3dViewport.MinDepth = fMinZ;
	m_d3dViewport.MaxDepth = fMaxZ;
	pd3dDeviceContext->RSSetViewports(1, &m_d3dViewport);
}

void CCamera::GenerateViewMatrix()
{
	XMStoreFloat4x4(&m_d3dxmtxView, XMMatrixLookAtLH(XMLoadFloat3(&m_d3dxvPosition), m_pPlayer->GetPositionXMV(), XMLoadFloat3(&m_d3dxvUp)));
}

void CCamera::RegenerateViewMatrix()
{
	//ī�޶��� z-�� ���͸� ����ȭ�Ѵ�.
	XMStoreFloat3(&m_d3dxvLook, XMVector3Normalize(XMLoadFloat3(&m_d3dxvLook)));
	//ī�޶��� z-��� y-�࿡ ������ ���͸� x-������ �����Ѵ�.
	XMStoreFloat3(&m_d3dxvRight, XMVector3Cross(XMLoadFloat3(&m_d3dxvUp), XMLoadFloat3(&m_d3dxvLook)));
	//ī�޶��� x-�� ���͸� ����ȭ�Ѵ�.
	XMStoreFloat3(&m_d3dxvRight, XMVector3Normalize(XMLoadFloat3(&m_d3dxvRight)));
	//ī�޶��� z-��� x-�࿡ ������ ���͸� y-������ �����Ѵ�.
	XMStoreFloat3(&m_d3dxvUp, XMVector3Cross(XMLoadFloat3(&m_d3dxvLook), XMLoadFloat3(&m_d3dxvRight)));
	//ī�޶��� y-�� ���͸� ����ȭ�Ѵ�.
	XMStoreFloat3(&m_d3dxvUp, XMVector3Normalize(XMLoadFloat3(&m_d3dxvUp)));
	
	m_d3dxmtxView._11 = m_d3dxvRight.x;
	m_d3dxmtxView._12 = m_d3dxvUp.x;
	m_d3dxmtxView._13 = m_d3dxvLook.x;
	m_d3dxmtxView._21 = m_d3dxvRight.y;
	m_d3dxmtxView._22 = m_d3dxvUp.y;
	m_d3dxmtxView._23 = m_d3dxvLook.y;
	m_d3dxmtxView._31 = m_d3dxvRight.z;
	m_d3dxmtxView._32 = m_d3dxvUp.z;
	m_d3dxmtxView._33 = m_d3dxvLook.z;
	XMVECTOR xmvPositionX = XMVector3Dot(XMLoadFloat3(&m_d3dxvPosition), XMLoadFloat3(&m_d3dxvRight));
	XMVECTOR xmvPositionY = XMVector3Dot(XMLoadFloat3(&m_d3dxvPosition), XMLoadFloat3(&m_d3dxvUp));
	XMVECTOR xmvPositionZ = XMVector3Dot(XMLoadFloat3(&m_d3dxvPosition), XMLoadFloat3(&m_d3dxvLook));
	XMStoreFloat(&m_d3dxmtxView._41, -xmvPositionX);
	XMStoreFloat(&m_d3dxmtxView._42, -xmvPositionY);
	XMStoreFloat(&m_d3dxmtxView._43, -xmvPositionZ);

	//ī�޶��� ��ġ�� ������ �ٲ��(ī�޶� ��ȯ ����� �ٲ��) ����ü ����� �ٽ� ����Ѵ�.
	CalculateFrustumPlanes();

}

void CCamera::GenerateProjectionMatrix(float fNearPlaneDistance, float fFarPlaneDistance, float fAspectRatio, float fFOVAngle)
{
	XMStoreFloat4x4(&m_d3dxmtxProjection, XMMatrixPerspectiveFovLH((float)XMConvertToRadians(fFOVAngle), fAspectRatio, fNearPlaneDistance,
		fFarPlaneDistance));
}

void CCamera::CreateShaderVariables(ID3D11Device * pd3dDevice)
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VS_CB_CAMERA);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pd3dDevice->CreateBuffer(&bd, NULL, &m_pd3dcbCamera);
}

void CCamera::UpdateShaderVariables(ID3D11DeviceContext * pd3dDeviceContext)
{
	D3D11_MAPPED_SUBRESOURCE d3dMappedResource;
	// ��� ������ �޸� �ּҸ� �����ͼ� ī�޶� ��ȯ ��İ� ���� ��ȯ ����� �����Ѵ�.
	// ���̴����� ����� ��� ���� �ٲ�� �Ϳ� �����϶�.
	pd3dDeviceContext->Map(m_pd3dcbCamera, 0, D3D11_MAP_WRITE_DISCARD, 0,
		&d3dMappedResource);
	VS_CB_CAMERA *pcbViewProjection = (VS_CB_CAMERA *)d3dMappedResource.pData;
	
	XMMATRIX xmmtxView = XMLoadFloat4x4(&m_d3dxmtxView);
	XMMATRIX xmmtxProjection = XMLoadFloat4x4(&m_d3dxmtxProjection);

	XMStoreFloat4x4(&(pcbViewProjection->m_d3dxmtxView), XMMatrixTranspose(xmmtxView));
	XMStoreFloat4x4(&(pcbViewProjection->m_d3dxmtxProjection), XMMatrixTranspose(xmmtxProjection));

	pd3dDeviceContext->Unmap(m_pd3dcbCamera, 0);

	// ��� ���۸� ����(VS_SLOT_CAMERA)�� �����Ѵ�.
	pd3dDeviceContext->VSSetConstantBuffers(VS_SLOT_CAMERA, 1, &m_pd3dcbCamera);
}

void CCamera::CalculateFrustumPlanes()
{
	/*ī�޶� ��ȯ ��İ� ���� ���� ��ȯ ����� ���� ����� ����Ͽ� ����ü ������ ���Ѵ�. �� ���� ��ǥ�迡�� ����ü �ø��� �Ѵ�.*/
	XMMATRIX mtxViewProject = XMLoadFloat4x4(&m_d3dxmtxView) * XMLoadFloat4x4(&m_d3dxmtxProjection);
	//BoundingFrustum::
	XMFLOAT4X4 xmf4x4ViewProject;
	XMStoreFloat4x4(&xmf4x4ViewProject, mtxViewProject);

	//����ü�� ���� ���
	m_d3dxFrustumPlanes[0].x = -(xmf4x4ViewProject._14 + xmf4x4ViewProject._11);
	m_d3dxFrustumPlanes[0].y = -(xmf4x4ViewProject._24 + xmf4x4ViewProject._21);
	m_d3dxFrustumPlanes[0].z = -(xmf4x4ViewProject._34 + xmf4x4ViewProject._31);
	m_d3dxFrustumPlanes[0].w = -(xmf4x4ViewProject._44 + xmf4x4ViewProject._41);

	//����ü�� ������ ���
	m_d3dxFrustumPlanes[1].x = -(xmf4x4ViewProject._14 - xmf4x4ViewProject._11);
	m_d3dxFrustumPlanes[1].y = -(xmf4x4ViewProject._24 - xmf4x4ViewProject._21);
	m_d3dxFrustumPlanes[1].z = -(xmf4x4ViewProject._34 - xmf4x4ViewProject._31);
	m_d3dxFrustumPlanes[1].w = -(xmf4x4ViewProject._44 - xmf4x4ViewProject._41);

	//����ü�� ���� ���
	m_d3dxFrustumPlanes[2].x = -(xmf4x4ViewProject._14 - xmf4x4ViewProject._12);
	m_d3dxFrustumPlanes[2].y = -(xmf4x4ViewProject._24 - xmf4x4ViewProject._22);
	m_d3dxFrustumPlanes[2].z = -(xmf4x4ViewProject._34 - xmf4x4ViewProject._32);
	m_d3dxFrustumPlanes[2].w = -(xmf4x4ViewProject._44 - xmf4x4ViewProject._42);

	//����ü�� �Ʒ��� ���
	m_d3dxFrustumPlanes[3].x = -(xmf4x4ViewProject._14 + xmf4x4ViewProject._12);
	m_d3dxFrustumPlanes[3].y = -(xmf4x4ViewProject._24 + xmf4x4ViewProject._22);
	m_d3dxFrustumPlanes[3].z = -(xmf4x4ViewProject._34 + xmf4x4ViewProject._32);
	m_d3dxFrustumPlanes[3].w = -(xmf4x4ViewProject._44 + xmf4x4ViewProject._42);

	//����ü�� �����
	m_d3dxFrustumPlanes[4].x = -(xmf4x4ViewProject._13);
	m_d3dxFrustumPlanes[4].y = -(xmf4x4ViewProject._23);
	m_d3dxFrustumPlanes[4].z = -(xmf4x4ViewProject._33);
	m_d3dxFrustumPlanes[4].w = -(xmf4x4ViewProject._43);

	//����ü�� �����
	m_d3dxFrustumPlanes[5].x = -(xmf4x4ViewProject._14 - xmf4x4ViewProject._13);
	m_d3dxFrustumPlanes[5].y = -(xmf4x4ViewProject._24 - xmf4x4ViewProject._23);
	m_d3dxFrustumPlanes[5].z = -(xmf4x4ViewProject._34 - xmf4x4ViewProject._33);
	m_d3dxFrustumPlanes[5].w = -(xmf4x4ViewProject._44 - xmf4x4ViewProject._43);

	XMVECTOR xmvFrustumPlanes[6];
	/*����ü�� �� ����� ���� ���� (a, b. c)�� ũ��� a, b, c, d�� ������. ��, ���� ���͸� ����ȭ�ϰ� �������� �������� �Ÿ��� ����Ѵ�.*/
	for (int i = 0; i < 6; i++)
	{
		xmvFrustumPlanes[i] = XMPlaneNormalize(XMLoadFloat4(&m_d3dxFrustumPlanes[i]));
	}
}

bool CCamera::IsInFrustum(XMFLOAT3& d3dxvMinimum, XMFLOAT3& d3dxvMaximum)
{
	XMFLOAT3 d3dxvNearPoint, d3dxvFarPoint, d3dxvNormal;
	for (int i = 0; i < 6; i++)
	{
		/*����ü�� �� ��鿡 ���Ͽ� �ٿ�� �ڽ��� �������� ����Ѵ�. �������� x, y, z ��ǥ�� ���� ������ �� ��Ұ� �����̸� �ٿ�� �ڽ��� �ִ����� ��ǥ�� �ǰ� �׷��� ������ �ٿ�� �ڽ��� �ּ����� ��ǥ�� �ȴ�.*/
		d3dxvNormal = XMFLOAT3(m_d3dxFrustumPlanes[i].x, m_d3dxFrustumPlanes[i].y, m_d3dxFrustumPlanes[i].z);
		if (d3dxvNormal.x >= 0.0f)
		{
			if (d3dxvNormal.y >= 0.0f)
			{
				if (d3dxvNormal.z >= 0.0f)
				{
					//���� ������ x, y, z ��ǥ�� ��ȣ�� ��� ����̹Ƿ� �������� �ٿ�� �ڽ��� �ּ����̴�.
					d3dxvNearPoint.x = d3dxvMinimum.x; d3dxvNearPoint.y = d3dxvMinimum.y; d3dxvNearPoint.z = d3dxvMinimum.z;
				}
				else
				{
					/*���� ������ x, y ��ǥ�� ��ȣ�� ��� ����̹Ƿ� �������� x, y ��ǥ�� �ٿ�� �ڽ��� �ּ����� x, y ��ǥ�̰� ���� ������ z ��ǥ�� ����̹Ƿ� �������� z ��ǥ�� �ٿ�� �ڽ��� �ִ����� z ��ǥ�̴�.*/
					d3dxvNearPoint.x = d3dxvMinimum.x; d3dxvNearPoint.y = d3dxvMinimum.y; d3dxvNearPoint.z = d3dxvMaximum.z;
				}
			}
			else
			{
				if (d3dxvNormal.z >= 0.0f)
				{
					/*���� ������ x, z ��ǥ�� ��ȣ�� ��� ����̹Ƿ� �������� x, z ��ǥ�� �ٿ�� �ڽ��� �ּ����� x, z ��ǥ�̰� ���� ������ y ��ǥ�� ����̹Ƿ� �������� y ��ǥ�� �ٿ�� �ڽ��� �ִ����� y ��ǥ�̴�.*/
					d3dxvNearPoint.x = d3dxvMinimum.x; d3dxvNearPoint.y = d3dxvMaximum.y; d3dxvNearPoint.z = d3dxvMinimum.z;
				}
				else
				{
					/*���� ������ y, z ��ǥ�� ��ȣ�� ��� �����̹Ƿ� �������� y, z ��ǥ�� �ٿ�� �ڽ��� �ִ����� y, z ��ǥ�̰� ���� ������ x ��ǥ�� ����̹Ƿ� �������� x ��ǥ�� �ٿ�� �ڽ��� �ּ����� x ��ǥ�̴�.*/
					d3dxvNearPoint.x = d3dxvMinimum.x; d3dxvNearPoint.y = d3dxvMaximum.y; d3dxvNearPoint.z = d3dxvMaximum.z;
				}
			}
		}
		else
		{
			if (d3dxvNormal.y >= 0.0f)
			{
				if (d3dxvNormal.z >= 0.0f)
				{
					/*���� ������ y, z ��ǥ�� ��ȣ�� ��� ����̹Ƿ� �������� y, z ��ǥ�� �ٿ�� �ڽ��� �ּ����� y, z ��ǥ�̰� ���� ������ x ��ǥ�� �����̹Ƿ� �������� x ��ǥ�� �ٿ�� �ڽ��� �ִ����� x ��ǥ�̴�.*/
					d3dxvNearPoint.x = d3dxvMaximum.x; d3dxvNearPoint.y = d3dxvMinimum.y; d3dxvNearPoint.z = d3dxvMinimum.z;
				}
				else
				{
					/*���� ������ x, z ��ǥ�� ��ȣ�� ��� �����̹Ƿ� �������� x, z ��ǥ�� �ٿ�� �ڽ��� �ִ����� x, z ��ǥ�̰� ���� ������ y ��ǥ�� ����̹Ƿ� �������� y ��ǥ�� �ٿ�� �ڽ��� �ּ����� y ��ǥ�̴�.*/
					d3dxvNearPoint.x = d3dxvMaximum.x; d3dxvNearPoint.y = d3dxvMinimum.y; d3dxvNearPoint.z = d3dxvMaximum.z;
				}
			}
			else
			{
				if (d3dxvNormal.z >= 0.0f)
				{
					/*���� ������ x, y ��ǥ�� ��ȣ�� ��� �����̹Ƿ� �������� x, y ��ǥ�� �ٿ�� �ڽ��� �ִ����� x, y ��ǥ�̰� ���� ������ z ��ǥ�� ����̹Ƿ� �������� z ��ǥ�� �ٿ�� �ڽ��� �ּ����� z ��ǥ�̴�.*/
					d3dxvNearPoint.x = d3dxvMaximum.x; d3dxvNearPoint.y = d3dxvMaximum.y; d3dxvNearPoint.z = d3dxvMinimum.z;
				}
				else
				{
					//���� ������ x, y, z ��ǥ�� ��ȣ�� ��� �����̹Ƿ� �������� �ٿ�� �ڽ��� �ִ����̴�.
					d3dxvNearPoint.x = d3dxvMaximum.x; d3dxvNearPoint.y = d3dxvMaximum.y; d3dxvNearPoint.z = d3dxvMaximum.z;
				}
			}
		}
		XMStoreFloat3(&d3dxvNormal, XMVector3Dot(XMLoadFloat3(&d3dxvNormal), XMLoadFloat3(&d3dxvNearPoint)));
		if (d3dxvNormal.x + m_d3dxFrustumPlanes[i].w > 0.0f)
			return (false);
	}
	return(true);
}

bool CCamera::IsInFrustum(AABB * pAABB)
{
	return(IsInFrustum(pAABB->m_d3dxvMinimum, pAABB->m_d3dxvMaximum));
}

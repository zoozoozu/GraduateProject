#include "stdafx.h"
#include "BillboardObject.h"

CBillboardObject::CBillboardObject(CCamera* camera, int nMeshes)
	: CGameObject(nMeshes)
{
	m_pCamera = camera;
}

void CBillboardObject::SetLookAt(XMVECTOR& d3dxvTarget)
{
	XMVECTOR d3dxvRight;
	XMFLOAT3 d3dxvUp(0.0f, 1.0f, 0.0f);
	XMFLOAT3 d3dxvPosition(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43);
	XMFLOAT3 d3dxvLook;
	XMStoreFloat3(&d3dxvLook, d3dxvTarget);
	d3dxvLook.x = d3dxvLook.x - d3dxvPosition.x;
	d3dxvLook.y = d3dxvLook.y - d3dxvPosition.y;
	d3dxvLook.z = d3dxvLook.z - d3dxvPosition.z;


	XMStoreFloat3(&d3dxvLook, XMVector3Normalize(XMLoadFloat3(&d3dxvLook)));

	//D3DXVec3Normalize(&d3dxvLook, &d3dxvLook);
	d3dxvRight = XMVector3Cross(XMLoadFloat3(&d3dxvLook), XMLoadFloat3(&d3dxvUp));
	d3dxvRight = XMVector3Normalize(d3dxvRight);

	XMFLOAT3 floatRight(0.0f, 1.0f, 0.0f);
	XMStoreFloat3(&floatRight, d3dxvRight);

	m_xmf4x4World._11 = floatRight.x; m_xmf4x4World._12 = floatRight.y; m_xmf4x4World._13 = floatRight.z;
	m_xmf4x4World._21 = d3dxvUp.x; m_xmf4x4World._22 = d3dxvUp.y; m_xmf4x4World._23 = d3dxvUp.z;
	m_xmf4x4World._31 = d3dxvLook.x; m_xmf4x4World._32 = d3dxvLook.y; m_xmf4x4World._33 = d3dxvLook.z;
}

void CBillboardObject::Animate(float fTimeElapsed)
{
	XMMATRIX mtxWorld = XMLoadFloat4x4(&m_xmf4x4World);
	//XMMATRIX mtxScale = XMLoadFloat4x4(&m_d3dxmtxScale);
	//XMMATRIX mtxRotate = XMLoadFloat4x4(&m_d3dxmtxRotate);
	//XMMATRIX mtxTranslate = XMLoadFloat4x4(&m_d3dxmtxTranlate);
	//mtxWorld = mtxScale * mtxRotate * mtxTranslate;

	XMStoreFloat4x4(&m_xmf4x4World, mtxWorld);
	XMFLOAT3 d3dxvCameraPosition = m_pCamera->GetPosition();
	SetLookAt(XMLoadFloat3(&d3dxvCameraPosition));
}


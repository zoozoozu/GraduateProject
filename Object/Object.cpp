#include "stdafx.h"
#include "Shader/Shader.h"
#include "Object/Object.h"
#include "Material/Texture/Texture.h"
#include "Material/Material.h"


CGameObject::CGameObject(int nMeshes)
{
	XMStoreFloat4x4(&m_d3dxmtxWorld, XMMatrixIdentity());
	m_nMeshes = nMeshes;
	m_ppMeshes = NULL;
	if (m_nMeshes > 0) m_ppMeshes = new CMesh*[m_nMeshes];
	for (int i = 0; i < m_nMeshes; i++)m_ppMeshes[i] = NULL;

	m_bcMeshBoundingCube = AABB();		

	m_bActive = true;

	m_pTexture = nullptr;
	m_pMaterial = nullptr;

	m_nReferences = 0;
}


CGameObject::~CGameObject()
{
	if (m_ppMeshes)
	{
		for (int i = 0; i < m_nMeshes; i++)
		{
			if (m_ppMeshes[i]) m_ppMeshes[i]->Release();
			m_ppMeshes[i] = NULL;
		}
		delete[] m_ppMeshes;
	}

	if (m_pTexture)
		m_pTexture->Release();

	if (m_pMaterial) 
		m_pMaterial->Release();


}

void CGameObject::AddRef()
{
	m_nReferences++;
}

void CGameObject::Release()
{
	if (m_nReferences > 0)
		m_nReferences--;
	if (m_nReferences <= 0)
		delete this;
}

void CGameObject::SetMesh(CMesh *pMesh, int nIndex)
{
	if (m_ppMeshes)
	{
		if (m_ppMeshes[nIndex]) m_ppMeshes[nIndex]->Release();
		m_ppMeshes[nIndex] = pMesh;
		if (pMesh) pMesh->AddRef();
	}

	if (pMesh)
	{
		AABB bcBoundingCube = pMesh->GetBoundingCube();
		m_bcMeshBoundingCube.Merge(&bcBoundingCube);
	}

}

void CGameObject::Animate(float fTimeElapsed)
{
}

void CGameObject::Render(ID3D11DeviceContext * pd3dDeviceContext, CCamera *pCamera)
{
	CShader::UpdateShaderVariable(pd3dDeviceContext, XMLoadFloat4x4(&m_d3dxmtxWorld));
	
	if(m_pMaterial)
	CIlluminatedShader::UpdateShaderVariable(pd3dDeviceContext, &m_pMaterial->m_Material);
	
	//객체의 텍스쳐를 쉐이더 변수에 설정(연결)한다.
	if (m_pTexture) 
		m_pTexture->UpdateShaderVariable(pd3dDeviceContext);

	if (m_ppMeshes)
	{
		for (int i = 0; i < m_nMeshes; i++)
		{
			if (m_ppMeshes[i]) m_ppMeshes[i]->Render(pd3dDeviceContext);
		}
	}
}

void CGameObject::SetMaterial(CMaterial * pMaterial)
{
	if (m_pMaterial) m_pMaterial->Release();
	m_pMaterial = pMaterial;
	if (m_pMaterial) m_pMaterial->AddRef();
}

void CGameObject::SetTexture(CTexture * pTexture)
{
	if (m_pTexture) m_pTexture->Release();
	m_pTexture = pTexture;
	if (m_pTexture) m_pTexture->AddRef();

}

void CGameObject::SetPosition(float x, float y, float z)
{
	m_d3dxmtxWorld._41 = x;
	m_d3dxmtxWorld._42 = y;
	m_d3dxmtxWorld._43 = z;
}

void CGameObject::SetPosition(XMFLOAT3& d3dxvPosition)
{
	m_d3dxmtxWorld._41 = d3dxvPosition.x;
	m_d3dxmtxWorld._42 = d3dxvPosition.y;
	m_d3dxmtxWorld._43 = d3dxvPosition.z;
}

XMFLOAT3& CGameObject::GetPosition()
{
	return (XMFLOAT3(m_d3dxmtxWorld._41, m_d3dxmtxWorld._42, m_d3dxmtxWorld._43));
}

void CGameObject::MoveStrafe(float fDistance)
{
	//게임 객체를 로컬 x-축 방향으로 이동한다.
	XMVECTOR d3dxvPosition = GetPositionXMV();
	XMVECTOR d3dxvRight = GetRightXMV();
	d3dxvPosition += fDistance * d3dxvRight;
	XMFLOAT3 xmfPosition;
	XMStoreFloat3(&xmfPosition, d3dxvPosition);
	CGameObject::SetPosition(xmfPosition);
}

void CGameObject::MoveUp(float fDistance)
{
	//게임 객체를 로컬 y-축 방향으로 이동한다.
	XMVECTOR d3dxvPosition = GetPositionXMV();
	XMVECTOR d3dxvUp = GetUpXMV();
	d3dxvPosition += fDistance * d3dxvUp;
	XMFLOAT3 xmfPosition;
	XMStoreFloat3(&xmfPosition, d3dxvPosition);
	CGameObject::SetPosition(xmfPosition);

}

void CGameObject::MoveForward(float fDistance)
{
	//게임 객체를 로컬 z-축 방향으로 이동한다.
	XMVECTOR d3dxvPosition = GetPositionXMV();
	XMVECTOR d3dxvLookAt = GetLookAtXMV();
	d3dxvPosition += fDistance * d3dxvLookAt;
	XMFLOAT3 xmfPosition;
	XMStoreFloat3(&xmfPosition, d3dxvPosition);
	CGameObject::SetPosition(xmfPosition);
}

void CGameObject::Rotate(float fPitch, float fYaw, float fRoll)
{
	//게임 객체를 주어진 각도로 회전한다.
	XMMATRIX mtxRotate;
	mtxRotate = XMMatrixRotationRollPitchYaw(XMConvertToRadians(fRoll), XMConvertToRadians(fPitch), XMConvertToRadians(fYaw));
	XMMATRIX xmmtxWorld = XMLoadFloat4x4(&m_d3dxmtxWorld);
	xmmtxWorld = mtxRotate * xmmtxWorld;
	XMStoreFloat4x4(&m_d3dxmtxWorld, xmmtxWorld);
}

void CGameObject::Rotate(XMVECTOR pd3dxvAxis, float fAngle)
{
	//게임 객체를 주어진 회전축을 중심으로 회전한다.
	XMMATRIX mtxRotate;
	mtxRotate = XMMatrixRotationAxis(pd3dxvAxis, XMConvertToRadians(fAngle));
	XMMATRIX xmmtxWorld = XMLoadFloat4x4(&m_d3dxmtxWorld);
	xmmtxWorld = mtxRotate * xmmtxWorld;
	XMStoreFloat4x4(&m_d3dxmtxWorld, xmmtxWorld);
}

CRotatingObject::CRotatingObject(int nMeshes)
{
	m_fRotationSpeed = 15.0f;
}

CRotatingObject::~CRotatingObject()
{
}

void CRotatingObject::Animate(float fTimeElapsed)
{
	XMMATRIX mtxRotate;
	mtxRotate = XMMatrixRotationY(XMConvertToRadians(45.0f * fTimeElapsed));
	XMStoreFloat4x4(&m_d3dxmtxWorld, mtxRotate * XMLoadFloat4x4(&m_d3dxmtxWorld));
}

void CRotatingObject::Render(ID3D11DeviceContext * pd3dDeviceContext, CCamera *pCamera)
{
	CGameObject::Render(pd3dDeviceContext, pCamera);
}

XMFLOAT3 CGameObject::GetLookAt()
{
	//게임 객체를 로컬 z-축 벡터를 반환한다.
	XMFLOAT3 d3dxvLookAt(m_d3dxmtxWorld._31, m_d3dxmtxWorld._32, m_d3dxmtxWorld._33);
	XMStoreFloat3(&d3dxvLookAt, XMVector3Normalize(XMLoadFloat3(&d3dxvLookAt)));
	return(d3dxvLookAt);
}

XMFLOAT3 CGameObject::GetUp()
{
	//게임 객체를 로컬 y-축 벡터를 반환한다.
	XMFLOAT3 d3dxvUp(m_d3dxmtxWorld._21, m_d3dxmtxWorld._22, m_d3dxmtxWorld._23);
	XMStoreFloat3(&d3dxvUp, XMVector3Normalize(XMLoadFloat3(&d3dxvUp)));
	return(d3dxvUp);
}

XMFLOAT3 CGameObject::GetRight()
{
	//게임 객체를 로컬 x-축 벡터를 반환한다.
	XMFLOAT3 d3dxvRight(m_d3dxmtxWorld._11, m_d3dxmtxWorld._12, m_d3dxmtxWorld._13);
	XMStoreFloat3(&d3dxvRight, XMVector3Normalize(XMLoadFloat3(&d3dxvRight)));
	return(d3dxvRight);
}

XMVECTOR CGameObject::GetPositionXMV()
{
	XMVECTOR xmvPosition = XMVectorSet(m_d3dxmtxWorld._41, m_d3dxmtxWorld._42, m_d3dxmtxWorld._43, 0.0f);
	xmvPosition = XMVector3Normalize(xmvPosition);
	return xmvPosition;
}

XMVECTOR CGameObject::GetLookAtXMV()
{
	XMVECTOR xmvLookAt = XMVectorSet(m_d3dxmtxWorld._31, m_d3dxmtxWorld._32, m_d3dxmtxWorld._33, 1.0f);
	xmvLookAt = XMVector3Normalize(xmvLookAt);
	return xmvLookAt;
}

XMVECTOR CGameObject::GetUpXMV()
{
	XMVECTOR xmvUp = XMVectorSet(m_d3dxmtxWorld._21, m_d3dxmtxWorld._22, m_d3dxmtxWorld._23, 1.0f);
	xmvUp = XMVector3Normalize(xmvUp);
	return xmvUp;
}

XMVECTOR CGameObject::GetRightXMV()
{
	XMVECTOR xmvRight = XMVectorSet(m_d3dxmtxWorld._11, m_d3dxmtxWorld._12, m_d3dxmtxWorld._13, 1.0f);
	xmvRight = XMVector3Normalize(xmvRight);
	return xmvRight;
}

bool CGameObject::IsVisible(CCamera *pCamera)
{
	OnPrepareRender();

	bool bIsVisible = false;
	if (m_bActive)
	{
		AABB bcBoundingCube = m_bcMeshBoundingCube;

		/*객체의 메쉬의 바운딩 박스(모델 좌표계)를 객체의 월드 변환 행렬로 변환하고 새로운 바운딩 박스를 계산한다.*/
		bcBoundingCube.Update(XMLoadFloat4x4(&m_d3dxmtxWorld));
		if (pCamera) bIsVisible = pCamera->IsInFrustum(&bcBoundingCube);
	}

	return(bIsVisible);
}

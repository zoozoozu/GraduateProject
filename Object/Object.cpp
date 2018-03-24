#include "stdafx.h"
#include "Shader/Shader.h"
#include "Object/Object.h"
#include "Material/Texture/Texture.h"
#include "Material/Material.h"


CGameObject::CGameObject(int nMeshes)
{
	m_xmf4x4ToParentTransform = Matrix4x4::Identity();
	m_xmf4x4World = Matrix4x4::Identity();

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
	CShader::UpdateShaderVariable(pd3dDeviceContext, XMLoadFloat4x4(&m_xmf4x4World));
	
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
	m_xmf4x4ToParentTransform._41 = x;
	m_xmf4x4ToParentTransform._42 = y;
	m_xmf4x4ToParentTransform._43 = z;
}

void CGameObject::SetPosition(XMFLOAT3& xmf3Position)
{
	SetPosition(xmf3Position.x, xmf3Position.y, xmf3Position.z);
}

void CGameObject::SetLocalPosition(XMFLOAT3 & xmf3Position)
{
	XMMATRIX mtxTranslation = XMMatrixTranslation(xmf3Position.x, xmf3Position.y, xmf3Position.z);
	m_xmf4x4ToParentTransform = Matrix4x4::Multiply(m_xmf4x4ToParentTransform, mtxTranslation);
}

XMFLOAT3& CGameObject::GetPosition()
{
	return (XMFLOAT3(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43));
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
	XMMATRIX mtxRotate = XMMatrixRotationRollPitchYaw(XMConvertToRadians(fPitch), XMConvertToRadians(fYaw), XMConvertToRadians(fRoll));
	m_xmf4x4ToParentTransform = Matrix4x4::Multiply(mtxRotate, m_xmf4x4ToParentTransform);
}

void CGameObject::Rotate(XMVECTOR pd3dxvAxis, float fAngle)
{
	//게임 객체를 주어진 회전축을 중심으로 회전한다.
	XMMATRIX mtxRotate = XMMatrixRotationAxis(pd3dxvAxis, XMConvertToRadians(fAngle));
	m_xmf4x4ToParentTransform = Matrix4x4::Multiply(mtxRotate, m_xmf4x4ToParentTransform);
}

void CGameObject::UpdateTransform(XMFLOAT4X4 * pxmf4x4Parent)
{
	m_xmf4x4World = (pxmf4x4Parent) ? Matrix4x4::Multiply(m_xmf4x4ToParentTransform, *pxmf4x4Parent) : m_xmf4x4ToParentTransform;

	//if (m_pSibling) m_pSibling->UpdateTransform(pxmf4x4Parent);
	//if (m_pChild) m_pChild->UpdateTransform(&m_xmf4x4World);
}

XMFLOAT3 CGameObject::GetLookAt()
{
	//게임 객체를 로컬 z-축 벡터를 반환한다.
	XMFLOAT3 d3dxvLookAt(m_xmf4x4World._31, m_xmf4x4World._32, m_xmf4x4World._33);
	XMStoreFloat3(&d3dxvLookAt, XMVector3Normalize(XMLoadFloat3(&d3dxvLookAt)));
	return(d3dxvLookAt);
}

XMFLOAT3 CGameObject::GetUp()
{
	//게임 객체를 로컬 y-축 벡터를 반환한다.
	XMFLOAT3 d3dxvUp(m_xmf4x4World._21, m_xmf4x4World._22, m_xmf4x4World._23);
	XMStoreFloat3(&d3dxvUp, XMVector3Normalize(XMLoadFloat3(&d3dxvUp)));
	return(d3dxvUp);
}

XMFLOAT3 CGameObject::GetRight()
{
	//게임 객체를 로컬 x-축 벡터를 반환한다.
	XMFLOAT3 d3dxvRight(m_xmf4x4World._11, m_xmf4x4World._12, m_xmf4x4World._13);
	XMStoreFloat3(&d3dxvRight, XMVector3Normalize(XMLoadFloat3(&d3dxvRight)));
	return(d3dxvRight);
}

XMVECTOR CGameObject::GetPositionXMV()
{
	XMVECTOR xmvPosition = XMVectorSet(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43, 0.0f);
	xmvPosition = XMVector3Normalize(xmvPosition);
	return xmvPosition;
}

XMVECTOR CGameObject::GetLookAtXMV()
{
	XMVECTOR xmvLookAt = XMVectorSet(m_xmf4x4World._31, m_xmf4x4World._32, m_xmf4x4World._33, 1.0f);
	xmvLookAt = XMVector3Normalize(xmvLookAt);
	return xmvLookAt;
}

XMVECTOR CGameObject::GetUpXMV()
{
	XMVECTOR xmvUp = XMVectorSet(m_xmf4x4World._21, m_xmf4x4World._22, m_xmf4x4World._23, 1.0f);
	xmvUp = XMVector3Normalize(xmvUp);
	return xmvUp;
}

XMVECTOR CGameObject::GetRightXMV()
{
	XMVECTOR xmvRight = XMVectorSet(m_xmf4x4World._11, m_xmf4x4World._12, m_xmf4x4World._13, 1.0f);
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
		bcBoundingCube.Update(XMLoadFloat4x4(&m_xmf4x4World));
		if (pCamera) bIsVisible = pCamera->IsInFrustum(&bcBoundingCube);
	}

	return(bIsVisible);
}

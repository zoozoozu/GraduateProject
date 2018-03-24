#pragma once
#include "Camera\Camera.h"
#include "Mesh/Mesh.h"

class CTexture;
class CMaterial;

class CGameObject
{
private:
	int m_nReferences;

public:
	CGameObject(int nMeshes = 0);
	virtual ~CGameObject();

public:
	void AddRef();
	void Release();
	
protected:
	//자전 속도와 회전축 벡터를 나타내는 멤버 변수를 선언한다.
	float m_fRotationSpeed;
	XMFLOAT3 m_d3dxvRotationAxis;

public:
	bool m_bActive;
	//객체가 가지는 메쉬들에 대한 포인터와 그 개수이다.
	CMesh **m_ppMeshes;
	int m_nMeshes;

	//객체가 가지는 메쉬 전체에 대한 바운딩 박스이다.
	AABB m_bcMeshBoundingCube;

	void SetMesh(CMesh *pMesh, int nIndex = 0);
	CMesh *GetMesh(int nIndex = 0) { return(m_ppMeshes[nIndex]); }

	XMFLOAT4X4						m_xmf4x4ToParentTransform;
	XMFLOAT4X4						m_xmf4x4ToRootTransform;
	XMFLOAT4X4						m_xmf4x4World;

	virtual void Animate(float fTimeElapsed);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext, CCamera *pCamera);

	//게임 객체는 하나의 재질을 가질 수 있다.
	CMaterial *m_pMaterial;
	void SetMaterial(CMaterial *pMaterial);

	//게임 객체는 텍스쳐 가질 수 있다.
	CTexture *m_pTexture;
	void SetTexture(CTexture *pTexture);

public:
	// 객체의 위치를 설정한다.
	virtual void SetPosition(float x, float y, float z);
	virtual void SetPosition(XMFLOAT3& xmf3Position);
	virtual void SetLocalPosition(XMFLOAT3& xmf3Position);
	//자전 속도와 회전축 벡터를 설정하는 함수이다.
	virtual void SetRotationSpeed(float fRotationSpeed) { m_fRotationSpeed = fRotationSpeed; }
	virtual void SetRotationAxis(XMFLOAT3 d3dxvRotationAxis) { m_d3dxvRotationAxis = d3dxvRotationAxis; }

	//로컬 x-축, y-축, z-축 방향으로 이동한다.
	virtual void MoveStrafe(float fDistance = 1.0f);
	virtual void MoveUp(float fDistance = 1.0f);
	virtual void MoveForward(float fDistance = 1.0f);

	//로컬 x-축, y-축, z-축 방향으로 회전한다.
	virtual void Rotate(float fPitch = 10.0f, float fYaw = 10.0f, float fRoll = 10.0f);
	virtual void Rotate(XMVECTOR pd3dxvAxis, float fAngle);

	virtual void UpdateTransform(XMFLOAT4X4 *pxmf4x4Parent = NULL);

	//객체의 위치, 로컬 x-축, y-축, z-축 방향 벡터를 반환한다.
	XMFLOAT3& GetPosition();
	XMFLOAT3 GetLookAt();
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();

	XMVECTOR GetPositionXMV();
	XMVECTOR GetLookAtXMV();
	XMVECTOR GetUpXMV();
	XMVECTOR GetRightXMV();

	//객체를 렌더링하기 전에 호출되는 함수이다.
	virtual void OnPrepareRender() { }

	bool IsVisible(CCamera *pCamera = nullptr);

};
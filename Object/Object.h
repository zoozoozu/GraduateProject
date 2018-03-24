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
	//���� �ӵ��� ȸ���� ���͸� ��Ÿ���� ��� ������ �����Ѵ�.
	float m_fRotationSpeed;
	XMFLOAT3 m_d3dxvRotationAxis;

public:
	bool m_bActive;
	//��ü�� ������ �޽��鿡 ���� �����Ϳ� �� �����̴�.
	CMesh **m_ppMeshes;
	int m_nMeshes;

	//��ü�� ������ �޽� ��ü�� ���� �ٿ�� �ڽ��̴�.
	AABB m_bcMeshBoundingCube;

	void SetMesh(CMesh *pMesh, int nIndex = 0);
	CMesh *GetMesh(int nIndex = 0) { return(m_ppMeshes[nIndex]); }

	XMFLOAT4X4						m_xmf4x4ToParentTransform;
	XMFLOAT4X4						m_xmf4x4ToRootTransform;
	XMFLOAT4X4						m_xmf4x4World;

	virtual void Animate(float fTimeElapsed);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext, CCamera *pCamera);

	//���� ��ü�� �ϳ��� ������ ���� �� �ִ�.
	CMaterial *m_pMaterial;
	void SetMaterial(CMaterial *pMaterial);

	//���� ��ü�� �ؽ��� ���� �� �ִ�.
	CTexture *m_pTexture;
	void SetTexture(CTexture *pTexture);

public:
	// ��ü�� ��ġ�� �����Ѵ�.
	virtual void SetPosition(float x, float y, float z);
	virtual void SetPosition(XMFLOAT3& xmf3Position);
	virtual void SetLocalPosition(XMFLOAT3& xmf3Position);
	//���� �ӵ��� ȸ���� ���͸� �����ϴ� �Լ��̴�.
	virtual void SetRotationSpeed(float fRotationSpeed) { m_fRotationSpeed = fRotationSpeed; }
	virtual void SetRotationAxis(XMFLOAT3 d3dxvRotationAxis) { m_d3dxvRotationAxis = d3dxvRotationAxis; }

	//���� x-��, y-��, z-�� �������� �̵��Ѵ�.
	virtual void MoveStrafe(float fDistance = 1.0f);
	virtual void MoveUp(float fDistance = 1.0f);
	virtual void MoveForward(float fDistance = 1.0f);

	//���� x-��, y-��, z-�� �������� ȸ���Ѵ�.
	virtual void Rotate(float fPitch = 10.0f, float fYaw = 10.0f, float fRoll = 10.0f);
	virtual void Rotate(XMVECTOR pd3dxvAxis, float fAngle);

	virtual void UpdateTransform(XMFLOAT4X4 *pxmf4x4Parent = NULL);

	//��ü�� ��ġ, ���� x-��, y-��, z-�� ���� ���͸� ��ȯ�Ѵ�.
	XMFLOAT3& GetPosition();
	XMFLOAT3 GetLookAt();
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();

	XMVECTOR GetPositionXMV();
	XMVECTOR GetLookAtXMV();
	XMVECTOR GetUpXMV();
	XMVECTOR GetRightXMV();

	//��ü�� �������ϱ� ���� ȣ��Ǵ� �Լ��̴�.
	virtual void OnPrepareRender() { }

	bool IsVisible(CCamera *pCamera = nullptr);

};
#include "stdafx.h"
#include "Shader/SceneShader/SceneShader.h"
#include "Object/Object.h"
#include "Mesh/AABBBoundingMesh/AABBBoundingMesh.h"


CSceneShader::CSceneShader(int nObjects)
	:CDiffusedShader(nObjects)
{
}


CSceneShader::~CSceneShader()
{
}

void CSceneShader::CreateShader(ID3D11Device * pd3dDevice)
{
	CDiffusedShader::CreateShader(pd3dDevice);
}

void CSceneShader::BuildObjects(ID3D11Device * pd3dDevice)
{
	m_nObjects = 1;
	m_ppObjects = new CGameObject*[m_nObjects];

	CMesh *pCubeMesh = new CCubeMesh(pd3dDevice, 500.0f, 2.0f, 500.0f);
	//CMesh *pModelMesh = new CFbxModelMesh(pd3dDevice, "building-commercial_03.data", 1);
	CGameObject *pBuildingModel = new CGameObject(1);
	pBuildingModel->SetMesh(pCubeMesh);
	pBuildingModel->SetPosition(XMFLOAT3(500.0, 0.0, 500.0));
	pBuildingModel->SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 0.0f));
	pBuildingModel->SetRotationSpeed(0.0f);
	m_ppObjects[0] = pBuildingModel;
}

void CSceneShader::Render(ID3D11DeviceContext * pd3dDeviceContext, shared_ptr<CCamera> pCamera)
{
	CDiffusedShader::Render(pd3dDeviceContext, pCamera);
}

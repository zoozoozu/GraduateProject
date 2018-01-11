#include "stdafx.h"
#include "Mesh/AABBBoundingMesh/AABBBoundingMesh.h"
#include "Mesh/TerrainMesh/TerrainMesh.h"
#include "Object/Player/TerrainPlayer/TerrainPlayer.h"
#include "PlayerShader.h"


CPlayerShader::CPlayerShader()
{
}


CPlayerShader::~CPlayerShader()
{
}

//void CPlayerShader::CreateShader(ID3D11Device * pd3dDevice)
//{
//	CShader::CreateShader(pd3dDevice);
//}

void CPlayerShader::BuildObjects(ID3D11Device * pd3dDevice)
{
	m_nObjects = 1;
	m_ppObjects = new CGameObject*[m_nObjects];

	ID3D11DeviceContext *pd3dDeviceContext = NULL;
	pd3dDevice->GetImmediateContext(&pd3dDeviceContext);

	CMesh *pPlayerMesh = new CCubeMesh(pd3dDevice, 4.0f, 12.0f, 4.0f);
	CTerrainPlayer *pAirplanePlayer = new CTerrainPlayer(1);
	pAirplanePlayer->SetMesh(pPlayerMesh);
	pAirplanePlayer->CreateShaderVariables(pd3dDevice);
	pAirplanePlayer->ChangeCamera(pd3dDevice, THIRD_PERSON_CAMERA, 0.0f);

	/*CCamera *pCamera = pAirplanePlayer->GetCamera();
	pCamera->SetViewport(pd3dDeviceContext, 0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, 0.0f, 1.0f);
	pCamera->GenerateProjectionMatrix(1.01f, 5000.0f, ASPECT_RATIO, 60.0f);
	pCamera->GenerateViewMatrix();

	pAirplanePlayer->SetPosition(XMFLOAT3(0.0f, 10.0f, -50.0f));*/
	m_ppObjects[0] = pAirplanePlayer;

	if (pd3dDeviceContext) pd3dDeviceContext->Release();

}

void CPlayerShader::Render(ID3D11DeviceContext * pd3dDeviceContext, CCamera * pCamera)
{
	//3인칭 카메라일 때 플레이어를 렌더링한다.
	DWORD nCameraMode = (pCamera) ? pCamera->GetMode() : 0x00;
	if (nCameraMode == THIRD_PERSON_CAMERA)
	{
		CShader::Render(pd3dDeviceContext, pCamera);
	}

}

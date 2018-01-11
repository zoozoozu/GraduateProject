#include "stdafx.h"
#include "Object/Player/TerrainPlayer/TerrainPlayer.h"
#include "Camera/ThirdPersonCamera/ThirdPersonCamera.h"
#include "Object/HeightMapTerrain/HeightMapTerrain.h"


CTerrainPlayer::CTerrainPlayer(int nMeshes)
	:CPlayer(nMeshes)
{
}

CTerrainPlayer::~CTerrainPlayer()
{
}

void CTerrainPlayer::ChangeCamera(ID3D11Device * pd3dDevice, DWORD nNewCameraMode, float fTimeElapsed)
{
	DWORD nCurrentCameraMode = (m_pCamera) ? m_pCamera->GetMode() : 0x00;
	if (nCurrentCameraMode == nNewCameraMode) return;
	switch (nNewCameraMode)
	{
	case FIRST_PERSON_CAMERA:
		SetFriction(250.0f);
		//1인칭 카메라일 때 플레이어에 y-축 방향으로 중력이 작용한다.
		SetGravity(XMFLOAT3(0.0f, -300.0f, 0.0f));
		SetMaxVelocityXZ(300.0f);
		SetMaxVelocityY(400.0f);
		m_pCamera = OnChangeCamera(pd3dDevice, FIRST_PERSON_CAMERA, nCurrentCameraMode);
		m_pCamera->SetTimeLag(0.0f);
		m_pCamera->SetOffset(XMFLOAT3(0.0f, 20.0f, 0.0f));
		m_pCamera->GenerateProjectionMatrix(1.01f, 50000.0f, ASPECT_RATIO, 60.0f);
		break;
	case SPACESHIP_CAMERA:
		SetFriction(25.0f);
		//스페이스 쉽 카메라일 때 플레이어에 중력이 작용하지 않는다.
		SetGravity(XMFLOAT3(0.0f, 0.0f, 0.0f));
		SetMaxVelocityXZ(1000.0f);
		SetMaxVelocityY(1000.0f);
		m_pCamera = OnChangeCamera(pd3dDevice, SPACESHIP_CAMERA, nCurrentCameraMode);
		m_pCamera->SetTimeLag(0.0f);
		m_pCamera->SetOffset(XMFLOAT3(0.0f, 0.0f, 0.0f));
		m_pCamera->GenerateProjectionMatrix(1.01f, 50000.0f, ASPECT_RATIO, 60.0f);
		break;
	case THIRD_PERSON_CAMERA:
		SetFriction(250.0f);
		//3인칭 카메라일 때 플레이어에 y-축 방향으로 중력이 작용한다.
		SetGravity(XMFLOAT3(0.0f, -300.0f, 0.0f));
		SetMaxVelocityXZ(300.0f);
		SetMaxVelocityY(400.0f);
		m_pCamera = OnChangeCamera(pd3dDevice, THIRD_PERSON_CAMERA, nCurrentCameraMode);
		m_pCamera->SetTimeLag(0.25f);
		m_pCamera->SetOffset(XMFLOAT3(0.0f, 20.0f, -50.0f));
		m_pCamera->GenerateProjectionMatrix(1.01f, 50000.0f, ASPECT_RATIO, 60.0f);
		break;
	default:
		break;
	}
	Update(fTimeElapsed);
}

void CTerrainPlayer::OnPlayerUpdated(float fTimeElapsed)
{
	CHeightMapTerrain *pTerrain = (CHeightMapTerrain *)m_pPlayerUpdatedContext;
	XMFLOAT3 d3dxvScale = pTerrain->GetScale();
	XMFLOAT3 d3dxvPlayerPosition = GetPosition();
	int z = (int)(d3dxvPlayerPosition.z / d3dxvScale.z);
	bool bReverseQuad = ((z % 2) != 0);
	/*높이 맵에서 플레이어의 현재 위치 (x, z)의 y 값을 구한다. 그리고 플레이어 메쉬의 높이가 12이고 플레이어의 중심이 직육면체의 가운데이므로 y 값에 메쉬의 높이의 절반을 더하면 플레이어의 위치가 된다.*/
	float fHeight = pTerrain->GetHeight(d3dxvPlayerPosition.x, d3dxvPlayerPosition.z, bReverseQuad) + 6.0f;
	/*플레이어의 속도 벡터의 y-값이 음수이면(예를 들어, 중력이 적용되는 경우) 플레이어의 위치 벡터의 y-값이 점점 작아지게 된다. 이때 플레이어의 현재 위치의 y 값이 지형의 높이(실제로 지형의 높이 + 6)보다 작으면 플레이어가 땅속에 있게 되므로 플레이어의 속도 벡터의 y 값을 0으로 만들고 플레이어의 위치 벡터의 y-값을 지형의 높이로 설정한다. 그러면 플레이어는 지형 위에 있게 된다.*/
	if (d3dxvPlayerPosition.y < fHeight)
	{
		XMFLOAT3 d3dxvPlayerVelocity = GetVelocity();
		d3dxvPlayerVelocity.y = 0.0f;
		SetVelocity(d3dxvPlayerVelocity);
		d3dxvPlayerPosition.y = fHeight;
		SetPosition(d3dxvPlayerPosition);
	}
}

void CTerrainPlayer::OnCameraUpdated(float fTimeElapsed)
{
	CHeightMapTerrain *pTerrain = (CHeightMapTerrain *)m_pCameraUpdatedContext;
	XMFLOAT3 d3dxvScale = pTerrain->GetScale();
	CCamera *pCamera = GetCamera();
	XMFLOAT3 d3dxvCameraPosition = pCamera->GetPosition();
	int z = (int)(d3dxvCameraPosition.z / d3dxvScale.z);
	bool bReverseQuad = ((z % 2) != 0);
	/*높이 맵에서 카메라의 현재 위치 (x, z)의 높이(y 값)를 구한다. 이 값이 카메라의 위치에 해당하는 지형의 높이 보다 작으면 카메라가 땅속에 있게 된다. 이렇게 되면 <그림 4>의 왼쪽과 같이 지형이 그려지지 않는 경우가 발생한다(카메라가 지형 안에 있으므로 와인딩 순서가 바뀐다). 이러한 경우가 발생하지 않도록 카메라의 위치의 최소값은 (지형의 높이 + 5)로 설정한다. 카메라의 위치의 최소값은 지형의 모든 위치에서 카메라가 지형 아래에 위치하지 않도록 설정한다.*/
	float fHeight = pTerrain->GetHeight(d3dxvCameraPosition.x, d3dxvCameraPosition.z, bReverseQuad) + 5.0f;
	if (d3dxvCameraPosition.y < fHeight)
	{
		d3dxvCameraPosition.y = fHeight;
		pCamera->SetPosition(d3dxvCameraPosition);
		//3인칭 카메라의 경우 카메라의 y-위치가 변경되었으므로 카메라가 플레이어를 바라보도록 한다.
		if (pCamera->GetMode() == THIRD_PERSON_CAMERA)
		{
			CThirdPersonCamera *p3rdPersonCamera = (CThirdPersonCamera *)pCamera;
			p3rdPersonCamera->SetLookAt(XMLoadFloat3(&GetPosition()));
		}
	}
}


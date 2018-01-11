#pragma once
#include "Object/Object.h"
#include "HeightMap/HeightMap.h"

class CHeightMapTerrain :
	public CGameObject
{
public:
	CHeightMapTerrain(ID3D11Device *pd3dDevice, LPCTSTR pFileName, int nWidth, int nLength, int nBlockWidth, int nBlockLength, XMFLOAT3 d3dxvScale);
	virtual ~CHeightMapTerrain();

private:
	//지형의 높이 맵으로 사용할 이미지이다.
	CHeightMap *m_pHeightMap;

	//지형의 가로와 세로 크기이다.
	int m_nWidth;
	int m_nLength;

	//지형을 실제로 몇 배 확대할 것인가를 나타내는 스케일 벡터이다.
	XMFLOAT3 m_d3dxvScale;

public:
	//지형의 실제 높이를 반환한다. 높이 맵의 높이에 스케일을 곱한 값이다.
	float GetHeight(float x, float z, bool bReverseQuad = false) { return(m_pHeightMap->GetHeight(x, z, bReverseQuad) * m_d3dxvScale.y); }

	int GetHeightMapWidth() { return(m_pHeightMap->GetHeightMapWidth()); }
	int GetHeightMapLength() { return(m_pHeightMap->GetHeightMapLength()); }

	XMFLOAT3 GetScale() { return(m_d3dxvScale); }
	//지형의 실제 크기(가로/세로)를 반환한다. 높이 맵의 크기에 스케일을 곱한 값이다.
	float GetWidth() { return(m_nWidth * m_d3dxvScale.x); }
	float GetLength() { return(m_nLength * m_d3dxvScale.z); }

	float GetPeakHeight() { return(m_bcMeshBoundingCube.m_d3dxvMaximum.y); }

};


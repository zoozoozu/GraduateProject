#include "stdafx.h"
#include "Mesh/Mesh.h"
#include "HeightMap/HeightMap.h"
#include "Mesh/TerrainMesh/TerrainMesh.h"

CTerrainMesh::CTerrainMesh(ID3D11Device * pd3dDevice, int xStart, int zStart, int nWidth, int nLength, XMFLOAT3 d3dxvScale, void * pContext)
	:CMeshDetailTexturedIlluminated(pd3dDevice)
{
	m_nVertices = nWidth * nLength;
	m_d3dPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

	m_pd3dxvPositions = new XMFLOAT3[m_nVertices];
	XMFLOAT3 *pd3dxvNormals = new XMFLOAT3[m_nVertices];
	XMFLOAT2 *pd3dxvTexCoords = new XMFLOAT2[m_nVertices];
	XMFLOAT2 *pd3dxvDetailTexCoords = new XMFLOAT2[m_nVertices];

	m_nWidth = nWidth;
	m_nLength = nLength;
	m_d3dxvScale = d3dxvScale;

	CHeightMap *pHeightMap = (CHeightMap *)pContext;
	int cxHeightMap = pHeightMap->GetHeightMapWidth();
	int czHeightMap = pHeightMap->GetHeightMapLength();
	float fHeight = 0.0f, fMinHeight = +FLT_MAX, fMaxHeight = -FLT_MAX;
	for (int i = 0, z = zStart; z < (zStart + nLength); z++)
	{
		for (int x = xStart; x < (xStart + nWidth); x++, i++)
		{
			fHeight = OnGetHeight(x, z, pContext);
			m_pd3dxvPositions[i] = XMFLOAT3((x*m_d3dxvScale.x), fHeight, (z*m_d3dxvScale.z));
			pd3dxvTexCoords[i] = XMFLOAT2(float(x) / float(cxHeightMap - 1),
				float(czHeightMap - 1 - z) / float(czHeightMap - 1));
			pd3dxvDetailTexCoords[i] = XMFLOAT2(float(x) / float(m_d3dxvScale.x *0.5f),
				float(z) / float(m_d3dxvScale.z*0.5f));
			XMStoreFloat3(&pd3dxvNormals[i], pHeightMap->GetHeightMapNormal(x, z));
			if (fHeight < fMinHeight) fMinHeight = fHeight;
			if (fHeight > fMaxHeight) fMaxHeight = fHeight;
		}
	}

	D3D11_BUFFER_DESC d3dBufferDesc;
	ZeroMemory(&d3dBufferDesc, sizeof(D3D11_BUFFER_DESC));
	d3dBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	d3dBufferDesc.ByteWidth = sizeof(XMFLOAT3) * m_nVertices;
	d3dBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	d3dBufferDesc.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA d3dBufferData;
	ZeroMemory(&d3dBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
	d3dBufferData.pSysMem = m_pd3dxvPositions;
	pd3dDevice->CreateBuffer(&d3dBufferDesc, &d3dBufferData, &m_pd3dPositionBuffer);

	d3dBufferDesc.ByteWidth = sizeof(XMFLOAT3) * m_nVertices;
	d3dBufferData.pSysMem = pd3dxvNormals;
	pd3dDevice->CreateBuffer(&d3dBufferDesc, &d3dBufferData, &m_pd3dNormalBuffer);

	d3dBufferDesc.ByteWidth = sizeof(XMFLOAT2) * m_nVertices;
	d3dBufferData.pSysMem = pd3dxvTexCoords;
	pd3dDevice->CreateBuffer(&d3dBufferDesc, &d3dBufferData, &m_pd3dTexCoordBuffer);

	d3dBufferData.pSysMem = pd3dxvDetailTexCoords;
	pd3dDevice->CreateBuffer(&d3dBufferDesc, &d3dBufferData, &m_pd3dDetailTexCoordBuffer);

	if (pd3dxvNormals) delete[] pd3dxvNormals;
	if (pd3dxvTexCoords) delete[] pd3dxvTexCoords;
	if (pd3dxvDetailTexCoords) delete[] pd3dxvDetailTexCoords;

	ID3D11Buffer *pd3dBuffers[4] = { m_pd3dPositionBuffer, m_pd3dNormalBuffer, m_pd3dTexCoordBuffer, m_pd3dDetailTexCoordBuffer };
	UINT pnBufferStrides[4] = { sizeof(XMFLOAT3), sizeof(XMFLOAT3), sizeof(XMFLOAT2), sizeof(XMFLOAT2) };
	UINT pnBufferOffsets[4] = { 0, 0, 0, 0 };
	AssembleToVertexBuffer(4, pd3dBuffers, pnBufferStrides, pnBufferOffsets);

	m_nIndices = ((nWidth * 2)*(nLength - 1)) + ((nLength - 1) - 1);
	m_pnIndices = new UINT[m_nIndices];
	for (int j = 0, z = 0; z < nLength - 1; z++)
	{
		if ((z % 2) == 0)
		{
			for (int x = 0; x < nWidth; x++)
			{
				if ((x == 0) && (z > 0)) m_pnIndices[j++] = (UINT)(x + (z * nWidth));
				m_pnIndices[j++] = (UINT)(x + (z * nWidth));
				m_pnIndices[j++] = (UINT)((x + (z * nWidth)) + nWidth);
			}
		}
		else
		{
			for (int x = nWidth - 1; x >= 0; x--)
			{
				if (x == (nWidth - 1)) m_pnIndices[j++] = (UINT)(x + (z * nWidth));
				m_pnIndices[j++] = (UINT)(x + (z * nWidth));
				m_pnIndices[j++] = (UINT)((x + (z * nWidth)) + nWidth);
			}
		}
	}

	ZeroMemory(&d3dBufferDesc, sizeof(D3D11_BUFFER_DESC));
	d3dBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	d3dBufferDesc.ByteWidth = sizeof(UINT) * m_nIndices;
	d3dBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	d3dBufferDesc.CPUAccessFlags = 0;
	ZeroMemory(&d3dBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
	d3dBufferData.pSysMem = m_pnIndices;
	pd3dDevice->CreateBuffer(&d3dBufferDesc, &d3dBufferData, &m_pd3dIndexBuffer);

	m_bcBoundingCube.m_d3dxvMinimum = XMFLOAT3(xStart*m_d3dxvScale.x, fMinHeight, zStart*m_d3dxvScale.z);
	m_bcBoundingCube.m_d3dxvMaximum = XMFLOAT3((xStart + nWidth)*m_d3dxvScale.x, fMaxHeight, (zStart + nLength)*m_d3dxvScale.z);

	CreateRasterizerState(pd3dDevice);
}

CTerrainMesh::~CTerrainMesh()
{
}

float CTerrainMesh::OnGetHeight(int x, int z, void * pContext)
{
	CHeightMap *pHeightMap = (CHeightMap *)pContext;
	BYTE *pHeightMapImage = pHeightMap->GetHeightMapImage();
	XMFLOAT3 d3dxvScale = pHeightMap->GetScale();
	int nWidth = pHeightMap->GetHeightMapWidth();
	float fHeight = pHeightMapImage[x + (z*nWidth)] * d3dxvScale.y;
	return(fHeight);
}

void CTerrainMesh::CreateRasterizerState(ID3D11Device * pd3dDevice)
{
	D3D11_RASTERIZER_DESC d3dRasterizerDesc;
	ZeroMemory(&d3dRasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	d3dRasterizerDesc.CullMode = D3D11_CULL_BACK;
	d3dRasterizerDesc.FillMode = D3D11_FILL_SOLID;
	d3dRasterizerDesc.DepthClipEnable = true;
	pd3dDevice->CreateRasterizerState(&d3dRasterizerDesc, &m_pd3dRasterizerState);
}

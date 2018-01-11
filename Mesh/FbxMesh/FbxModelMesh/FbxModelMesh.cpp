#include "stdafx.h"
#include "Mesh/FbxMesh/FbxMesh.h"
#include "Mesh/FbxMesh/FbxModelMesh/FbxModelMesh.h"


CFbxModelMesh::CFbxModelMesh(ID3D11Device *pd3dDevice, char *pszFileName, float fSize)
	:CFbxMesh(pd3dDevice)
{
	m_fFBXModelSize = fSize;

	ifstream fin;

	int filename_length = strlen(pszFileName);
	char* ch = new char[200];
	char* sToken = new char[50];
	char* temp;
	fin.open(pszFileName);
	if (!fin.fail())
	{
		// 데이터를 읽어와 필요한 정점, 인덱스, 본, 애니메이션 수 파악
		fin.getline(ch, 200);
		fin.getline(ch, 200);
		m_nVertices = stoi(ch);
		fin.getline(ch, 200);
		m_nIndices = stoi(ch);
		fin.getline(ch, 200);
	
		// 정점 데이터를 저장
		fin.getline(ch, 200);
		m_pd3dxvPositions = new XMFLOAT3[m_nVertices];
		m_pd3dxvNormals = new XMFLOAT3[m_nVertices];
		m_pd3dxvTexCoords = new XMFLOAT2[m_nVertices];
	
		for (int i = 0; i < m_nVertices; i++)
		{
			// Vertice
			fin.getline(ch, 200);
			sToken = strtok_s(ch, " ", &temp);	 m_pd3dxvPositions[i].x = stof(sToken);
			sToken = strtok_s(NULL, " ", &temp); m_pd3dxvPositions[i].y = stof(sToken);
			sToken = strtok_s(NULL, " ", &temp); m_pd3dxvPositions[i].z = stof(sToken);
			// Normal
			fin.getline(ch, 200);
			sToken = strtok_s(ch, " ", &temp);   m_pd3dxvNormals[i].x = stof(sToken);
			sToken = strtok_s(NULL, " ", &temp); m_pd3dxvNormals[i].y = stof(sToken);
			sToken = strtok_s(NULL, " ", &temp); m_pd3dxvNormals[i].z = stof(sToken);
			// UV
			fin.getline(ch, 200);
			sToken = strtok_s(ch, " ", &temp);   m_pd3dxvTexCoords[i].x = stof(sToken);
			sToken = strtok_s(NULL, " ", &temp); m_pd3dxvTexCoords[i].y = stof(sToken);
		}

		// 인덱스 데이터 저장
		fin.getline(ch, 200);
		m_pnIndices = new UINT[m_nIndices];

		for (int i = 0; i < m_nIndices; i += 3)
		{
			fin.getline(ch, 200);
			sToken = strtok_s(ch, " ", &temp);   m_pnIndices[i] = stoi(sToken);
			sToken = strtok_s(NULL, " ", &temp); m_pnIndices[i + 1] = stoi(sToken);
			sToken = strtok_s(NULL, " ", &temp); m_pnIndices[i + 2] = stoi(sToken);
		}

	}
	fin.close();

	m_d3dPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	m_pd3dPositionBuffer = CreateBuffer(pd3dDevice, sizeof(XMFLOAT3), m_nVertices, m_pd3dxvPositions, D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_DEFAULT, 0);
	m_pd3dNormalBuffer = CreateBuffer(pd3dDevice, sizeof(XMFLOAT3), m_nVertices, m_pd3dxvNormals, D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_DEFAULT, 0);
	m_pd3dTexCoordBuffer = CreateBuffer(pd3dDevice, sizeof(XMFLOAT2), m_nVertices, m_pd3dxvTexCoords, D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_DEFAULT, 0);
	ID3D11Buffer *pd3dBuffers[3] = { m_pd3dPositionBuffer, m_pd3dNormalBuffer, m_pd3dTexCoordBuffer };
	UINT pnBufferStrides[3] = { sizeof(XMFLOAT3), sizeof(XMFLOAT3), sizeof(XMFLOAT2)};
	UINT pnBufferOffsets[3] = { 0, 0, 0 };
	AssembleToVertexBuffer(3, pd3dBuffers, pnBufferStrides, pnBufferOffsets);

	m_pd3dIndexBuffer = CreateBuffer(pd3dDevice, sizeof(UINT), m_nIndices, m_pnIndices, D3D11_BIND_INDEX_BUFFER, D3D11_USAGE_DEFAULT, 0);

	/*m_bcBoundingCube.m_d3dxvMinimum = XMFLOAT3(, fMinHeight, zStart*m_d3dxvScale.z);
	m_bcBoundingCube.m_d3dxvMaximum = XMFLOAT3((xStart + nWidth)*m_d3dxvScale.x, fMaxHeight, (zStart + nLength)*m_d3dxvScale.z);*/

	CreateRasterizerState(pd3dDevice);

}


CFbxModelMesh::~CFbxModelMesh()
{
}

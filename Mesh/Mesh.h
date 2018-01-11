#pragma once

struct MESHINTERSECTINFO {
	DWORD	m_dwFaceIndex;
	float	m_fU;
	float	m_fV;
	float	m_fDistance;
};

#define EPSILON				1.0e-10f

inline bool IsZero(float fValue) { return((fabsf(fValue) < EPSILON)); }
inline bool IsEqual(float fA, float fB) { return(::IsZero(fA - fB)); }
inline float InverseSqrt(float fValue) { return 1.0f / sqrtf(fValue); }
inline void Swap(float *pfS, float *pfT) { float fTemp = *pfS; *pfS = *pfT; *pfT = fTemp; }

extern bool RayIntersectTriangle(XMVECTOR *pd3dxvOrigin, XMVECTOR *pd3dxvDirection, XMVECTOR *pd3dxvP0, XMVECTOR *pd3dxvP1, XMVECTOR *pd3dxvP2, float *pfU, float *pfV, float *pfRayToTriangle);

/////////////////////////////////////////////////////////////////////////////////////////////////
//
class AABB
{
public:
	XMFLOAT3						m_d3dxvMinimum;
	XMFLOAT3						m_d3dxvMaximum;
	BoundingBox						m_aabox;
	int								m_collision;

public:
	AABB() { 
		m_d3dxvMinimum = XMFLOAT3(+FLT_MAX, +FLT_MAX, +FLT_MAX); 
		m_d3dxvMaximum = XMFLOAT3(-FLT_MAX, -FLT_MAX, -FLT_MAX); 
	};

	AABB(XMVECTOR d3dxvMinimum, XMVECTOR d3dxvMaximum) 
	{ 
		XMStoreFloat3(&m_d3dxvMinimum, d3dxvMinimum);
		XMStoreFloat3(&m_d3dxvMaximum, d3dxvMaximum);
	}

	void Merge(XMFLOAT3 d3dxvMinimum, XMFLOAT3 d3dxvMaximum);
	void Merge(AABB *pAABB);
	void Update(XMMATRIX& pd3dxmtxTransform);
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//
class CMesh
{
public:
	CMesh(ID3D11Device *pd3dDevice);
	virtual ~CMesh();

private:
	int								m_nReferences;

public:
	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }

protected:
	AABB							m_bcBoundingCube;

protected:
	D3D11_PRIMITIVE_TOPOLOGY		m_d3dPrimitiveTopology;

	UINT							m_nType;

	ID3D11Buffer					*m_pd3dPositionBuffer;
	ID3D11Buffer					*m_pd3dColorBuffer;

	ID3D11Buffer					**m_ppd3dVertexBuffers;

	int								m_nVertices;
	int								m_nBuffers;
	UINT							m_nSlot;
	UINT							m_nStartVertex;
	UINT							*m_pnVertexStrides;
	UINT							*m_pnVertexOffsets;

	ID3D11Buffer					*m_pd3dIndexBuffer;

	UINT							m_nIndices;
	UINT							m_nStartIndex;
	int								m_nBaseVertex;
	DXGI_FORMAT						m_dxgiIndexFormat;
	UINT							m_nIndexOffset;

	ID3D11RasterizerState			*m_pd3dRasterizerState;

	XMFLOAT3						*m_pd3dxvPositions;
	UINT							*m_pnIndices;

public:
	AABB GetBoundingCube() { return(m_bcBoundingCube); }

	void AssembleToVertexBuffer(int nBuffers = 0, ID3D11Buffer **m_pd3dBuffers = NULL, UINT *pnBufferStrides = NULL, UINT *pnBufferOffsets = NULL);

	virtual void CreateRasterizerState(ID3D11Device *pd3dDevice);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);
	virtual void RenderInstanced(ID3D11DeviceContext *pd3dDeviceContext, int nInstances = 0, int nStartInstance = 0);
	ID3D11Buffer* CreateBuffer(ID3D11Device *pd3dDevice, UINT nStride, int nElements, void *pBufferData, UINT nBindFlags, D3D11_USAGE d3dUsage, UINT nCPUAccessFlags);

	int CheckRayIntersection(XMVECTOR *pd3dxvRayPosition, XMVECTOR *pd3dxvRayDirection, MESHINTERSECTINFO *pd3dxIntersectInfo);
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//
class CMeshDiffused : public CMesh
{
public:
	CMeshDiffused(ID3D11Device *pd3dDevice);
	virtual ~CMeshDiffused();

protected:
	ID3D11Buffer					*m_pd3dColorBuffer;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//
class CMeshIlluminated : public CMesh
{
public:
	CMeshIlluminated(ID3D11Device *pd3dDevice);
	virtual ~CMeshIlluminated();

protected:
	ID3D11Buffer					*m_pd3dNormalBuffer;

public:
	XMVECTOR CalculateTriAngleNormal(UINT nIndex0, UINT nIndex1, UINT nIndex2);
	void SetTriAngleListVertexNormal(XMVECTOR *pd3dxvNormals);
	void SetAverageVertexNormal(XMVECTOR *pd3dxvNormals, int nPrimitives, int nOffset, bool bStrip);
	void CalculateVertexNormal(XMVECTOR *pd3dxvNormals);
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//
class CMeshTextured : public CMesh
{
public:
	CMeshTextured(ID3D11Device *pd3dDevice);
	virtual ~CMeshTextured();

protected:
	// �ؽ��� ������ �ϱ� ���Ͽ� �ؽ��� ��ǥ�� �ʿ��ϴ�.
	ID3D11Buffer *m_pd3dTexCoordBuffer;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//
class CMeshDetailTextured : public CMeshTextured
{
public:
	CMeshDetailTextured(ID3D11Device *pd3dDevice);
	virtual ~CMeshDetailTextured();

protected:
	ID3D11Buffer *m_pd3dDetailTexCoordBuffer;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//
class CMeshTexturedIlluminated : public CMeshIlluminated
{
protected:
	ID3D11Buffer *m_pd3dTexCoordBuffer;

public:
	CMeshTexturedIlluminated(ID3D11Device *pd3dDevice);
	virtual ~CMeshTexturedIlluminated();
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//
class CMeshDetailTexturedIlluminated : public CMeshIlluminated
{
protected:
	ID3D11Buffer *m_pd3dTexCoordBuffer;
	ID3D11Buffer *m_pd3dDetailTexCoordBuffer;

public:
	CMeshDetailTexturedIlluminated(ID3D11Device *pd3dDevice);
	virtual ~CMeshDetailTexturedIlluminated();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
////

#pragma once

#include "Object/Object.h"
#include "Camera/Camera.h"
#include "Object/Player/Player.h"
#include "Material/Material.h"

struct VS_CB_WORLD_MATRIX
{
	XMFLOAT4X4 m_d3dxmtxWorld;
};

class CShader
{
private:
	int m_nReferences;

public:
	CShader(int nObjects = 1);
	virtual ~CShader();

public:
	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }

protected:
	ID3D11InputLayout * m_pd3dVertexLayout					{ nullptr };
	ID3D11VertexShader *m_pd3dVertexShader					{ nullptr };
	ID3D11PixelShader *m_pd3dPixelShader					{ nullptr };
	ID3D11GeometryShader *m_pd3dGeometryShader				{ nullptr };

	// 쉐이더 객체가 게임 객체들의 리스트를 가진다.
	CGameObject **m_ppObjects;
	int m_nObjects;

	// Texture&Material
	CMaterial *m_pMaterial									{ nullptr };
	CTexture *m_pTexture									{ nullptr };

	// Mesh
	CMesh *m_pMesh											{ nullptr };

	// GameObjectCount
	int m_nIndexToAdd;
	//월드 변환 행렬을 위한 상수 버퍼는 하나만 있어도 되므로 정적 멤버로 선언한다.
	static ID3D11Buffer *m_pd3dcbWorldMatrix;

public:
	void CreateVertexShaderFromFile(ID3D11Device *pd3dDevice, WCHAR
		*pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderModel,
		ID3D11VertexShader **ppd3dVertexShader, D3D11_INPUT_ELEMENT_DESC *pd3dInputLayout,
		UINT nElements, ID3D11InputLayout **ppd3dVertexLayout);

	void CreateGeometryShaderFromFile(ID3D11Device *pd3dDevice, WCHAR *pszFileName, LPCSTR pszShaderName,
		LPCSTR pszShaderModel, ID3D11GeometryShader **ppd3dGeometryShader);

	void CreatePixelShaderFromFile(ID3D11Device *pd3dDevice, WCHAR *pszFileName,
		LPCSTR pszShaderName, LPCSTR pszShaderModel, ID3D11PixelShader **ppd3dPixelShader);

	virtual void CreateShader(ID3D11Device *pd3dDevice);

	// 쉐이더 클래스의 상수 버퍼를 생성하고 반환하는 멤버 함수를 선언한다.
	static void CreateShaderVariables(ID3D11Device *pd3dDevice);
	static void ReleaseShaderVariables();
	// 쉐이더 클래스의 상수 버퍼를 갱신하는 멤버 함수를 선언한다.
	static void UpdateShaderVariable(ID3D11DeviceContext *pd3dDeviceContext,
		XMMATRIX pd3dxmtxWorld);
	
	//게임 객체들을 생성하고 애니메이션 처리를 하고 렌더링하기 위한 함수이다.
	virtual void BuildObjects(ID3D11Device *pd3dDevice);
	virtual void ReleaseObjects();
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void OnPrepareRender(ID3D11DeviceContext *pd3dDeviceContext);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext, shared_ptr<CCamera>pCamera = NULL);

	virtual void AddObject(CGameObject *pGameObject);
};

class CDiffusedShader : public CShader
{
public:
	CDiffusedShader(int nObjects);
	virtual ~CDiffusedShader();

	virtual void CreateShader(ID3D11Device *pd3dDevice);
};


class CTexturedShader : public CShader
{
public:
	CTexturedShader(int nObjects);
	virtual ~CTexturedShader();

	virtual void CreateShader(ID3D11Device *pd3dDevice);
};

class CDetailTexturedShader : public CTexturedShader
{
public:
	CDetailTexturedShader(int nObjects);
	virtual ~CDetailTexturedShader();

	virtual void CreateShader(ID3D11Device *pd3dDevice);
};

class CIlluminatedShader : public CShader
{
public:
	CIlluminatedShader(int nObjects);
	virtual ~CIlluminatedShader();

	virtual void CreateShader(ID3D11Device *pd3dDevice);

	//재질을 설정하기 위한 상수 버퍼이다.
	static ID3D11Buffer	 *m_pd3dcbMaterial;

	static void CreateShaderVariables(ID3D11Device *pd3dDevice);
	static void ReleaseShaderVariables();
	//재질을 쉐이더 변수에 설정(연결)하기 위한 함수이다.
	static void UpdateShaderVariable(ID3D11DeviceContext *pd3dDeviceContext, MATERIAL *pMaterial);
};

class CTexturedIlluminatedShader : public CIlluminatedShader
{
public:
	CTexturedIlluminatedShader(int nObjects);
	virtual ~CTexturedIlluminatedShader();

	virtual void CreateShader(ID3D11Device *pd3dDevice);
};

class CDetailTexturedIlluminatedShader : public CTexturedIlluminatedShader
{
public:
	CDetailTexturedIlluminatedShader(int nObjects);
	virtual ~CDetailTexturedIlluminatedShader();

	virtual void CreateShader(ID3D11Device *pd3dDevice);
};


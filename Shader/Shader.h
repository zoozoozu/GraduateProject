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
	CShader();
	virtual ~CShader();

public:
	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }

protected:
	ID3D11InputLayout *m_pd3dVertexLayout;
	ID3D11VertexShader *m_pd3dVertexShader;
	ID3D11PixelShader *m_pd3dPixelShader;
	ID3D11GeometryShader *m_pd3dGeometryShader;

	//���̴� ��ü�� ���� ��ü���� ����Ʈ�� ������.
	CGameObject **m_ppObjects;
	int m_nObjects;

	//���� ��ȯ ����� ���� ��� ���۴� �ϳ��� �־ �ǹǷ� ���� ����� �����Ѵ�.
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

	// ���̴� Ŭ������ ��� ���۸� �����ϰ� ��ȯ�ϴ� ��� �Լ��� �����Ѵ�.
	static void CreateShaderVariables(ID3D11Device *pd3dDevice);
	static void ReleaseShaderVariables();
	// ���̴� Ŭ������ ��� ���۸� �����ϴ� ��� �Լ��� �����Ѵ�.
	static void UpdateShaderVariable(ID3D11DeviceContext *pd3dDeviceContext,
		XMMATRIX pd3dxmtxWorld);
	
	//���� ��ü���� �����ϰ� �ִϸ��̼� ó���� �ϰ� �������ϱ� ���� �Լ��̴�.
	virtual void BuildObjects(ID3D11Device *pd3dDevice);
	virtual void ReleaseObjects();
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void OnPrepareRender(ID3D11DeviceContext *pd3dDeviceContext);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext, CCamera *pCamera = NULL);

};

class CDiffusedShader : public CShader
{
public:
	CDiffusedShader();
	virtual ~CDiffusedShader();

	virtual void CreateShader(ID3D11Device *pd3dDevice);
};


class CTexturedShader : public CShader
{
public:
	CTexturedShader();
	virtual ~CTexturedShader();

	virtual void CreateShader(ID3D11Device *pd3dDevice);
};

class CDetailTexturedShader : public CTexturedShader
{
public:
	CDetailTexturedShader();
	virtual ~CDetailTexturedShader();

	virtual void CreateShader(ID3D11Device *pd3dDevice);
};

class CIlluminatedShader : public CShader
{
public:
	CIlluminatedShader();
	virtual ~CIlluminatedShader();

	virtual void CreateShader(ID3D11Device *pd3dDevice);

	//������ �����ϱ� ���� ��� �����̴�.
	static ID3D11Buffer	 *m_pd3dcbMaterial;

	static void CreateShaderVariables(ID3D11Device *pd3dDevice);
	static void ReleaseShaderVariables();
	//������ ���̴� ������ ����(����)�ϱ� ���� �Լ��̴�.
	static void UpdateShaderVariable(ID3D11DeviceContext *pd3dDeviceContext, MATERIAL *pMaterial);
};

class CTexturedIlluminatedShader : public CIlluminatedShader
{
public:
	CTexturedIlluminatedShader();
	virtual ~CTexturedIlluminatedShader();

	virtual void CreateShader(ID3D11Device *pd3dDevice);
};

class CDetailTexturedIlluminatedShader : public CTexturedIlluminatedShader
{
public:
	CDetailTexturedIlluminatedShader();
	virtual ~CDetailTexturedIlluminatedShader();

	virtual void CreateShader(ID3D11Device *pd3dDevice);
};


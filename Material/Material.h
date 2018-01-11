#pragma once

//������ ������ ��Ÿ���� ����ü�̴�.
struct MATERIAL
{
	XMFLOAT4 m_d3dxcAmbient;
	XMFLOAT4 m_d3dxcDiffuse;
	XMFLOAT4 m_d3dxcSpecular; //(r,g,b,a=power)
	XMFLOAT4 m_d3dxcEmissive;
};

class CMaterial
{
public:
	CMaterial();
	virtual ~CMaterial();

private:
	int m_nReferences;

public:
	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }

	MATERIAL m_Material;
};


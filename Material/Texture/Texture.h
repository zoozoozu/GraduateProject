#pragma once
class CTexture
{
public:
	CTexture(int nTextures = 1, int nSamplers = 1, int nTextureStartSlot = 0, int nSamplerStartSlot = 0);
	virtual ~CTexture();
private:
	int m_nReferences;

public:
	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }

private:
	//�ؽ��� ���ҽ��� �����̴�.
	int m_nTextures;
	ID3D11ShaderResourceView **m_ppd3dsrvTextures;
	//�ؽ��� ���ҽ��� ������ ���� �����̴�.
	int m_nTextureStartSlot;
	//���÷� ���� ��ü�� �����̴�.
	int m_nSamplers;
	ID3D11SamplerState **m_ppd3dSamplerStates;
	//���÷� ���� ��ü�� ������ ���� �����̴�.
	int m_nSamplerStartSlot;

public:
	void SetTexture(int nIndex, ID3D11ShaderResourceView *pd3dsrvTexture);
	void SetSampler(int nIndex, ID3D11SamplerState *pd3dSamplerState);
	//�ؽ��� ���ҽ��� ���÷� ���� ��ü�� ���� ���̴� ������ �����Ѵ�.
	void UpdateShaderVariable(ID3D11DeviceContext *pd3dDeviceContext);
	//�ؽ��� ���ҽ��� ���� ���̴� ������ �����Ѵ�.
	void UpdateTextureShaderVariable(ID3D11DeviceContext *pd3dDeviceContext, int nIndex = 0, int nSlot = 0);
	//���÷� ���� ��ü�� ���� ���̴� ������ �����Ѵ�.
	void UpdateSamplerShaderVariable(ID3D11DeviceContext *pd3dDeviceContext, int nIndex = 0, int nSlot = 0);
};



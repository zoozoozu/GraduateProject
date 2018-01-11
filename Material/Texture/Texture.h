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
	//텍스쳐 리소스의 개수이다.
	int m_nTextures;
	ID3D11ShaderResourceView **m_ppd3dsrvTextures;
	//텍스쳐 리소스를 연결할 시작 슬롯이다.
	int m_nTextureStartSlot;
	//샘플러 상태 객체의 개수이다.
	int m_nSamplers;
	ID3D11SamplerState **m_ppd3dSamplerStates;
	//샘플러 상태 객체를 연결할 시작 슬롯이다.
	int m_nSamplerStartSlot;

public:
	void SetTexture(int nIndex, ID3D11ShaderResourceView *pd3dsrvTexture);
	void SetSampler(int nIndex, ID3D11SamplerState *pd3dSamplerState);
	//텍스쳐 리소스와 샘플러 상태 객체에 대한 쉐이더 변수를 변경한다.
	void UpdateShaderVariable(ID3D11DeviceContext *pd3dDeviceContext);
	//텍스쳐 리소스에 대한 쉐이더 변수를 변경한다.
	void UpdateTextureShaderVariable(ID3D11DeviceContext *pd3dDeviceContext, int nIndex = 0, int nSlot = 0);
	//샘플러 상태 객체에 대한 쉐이더 변수를 변경한다.
	void UpdateSamplerShaderVariable(ID3D11DeviceContext *pd3dDeviceContext, int nIndex = 0, int nSlot = 0);
};



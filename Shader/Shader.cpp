#include "stdafx.h"
#include "Shader.h"

ID3D11Buffer *CShader::m_pd3dcbWorldMatrix = NULL;
ID3D11Buffer *CIlluminatedShader::m_pd3dcbMaterial = NULL;

CShader::CShader(int nObjects)
{
	m_ppObjects = NULL;

	m_nObjects = nObjects;
	if (m_nObjects > 0)
	{
		m_ppObjects = new CGameObject*[m_nObjects];
		for (int i = 0; i < m_nObjects; i++) m_ppObjects[i] = NULL;
	}

	m_pd3dVertexLayout = NULL;
	m_pd3dVertexShader = NULL;
	m_pd3dPixelShader = NULL;
	m_pd3dGeometryShader = NULL;

	m_nIndexToAdd = 0;
}


CShader::~CShader()
{
	if (m_pd3dVertexLayout) m_pd3dVertexLayout->Release();
	if (m_pd3dVertexShader) m_pd3dVertexShader->Release();
	if (m_pd3dGeometryShader) m_pd3dGeometryShader->Release();
	if (m_pd3dPixelShader) m_pd3dPixelShader->Release();
}

void CShader::CreateVertexShaderFromFile(ID3D11Device * pd3dDevice, WCHAR * pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderModel, ID3D11VertexShader ** ppd3dVertexShader, D3D11_INPUT_ELEMENT_DESC * pd3dInputLayout, UINT nElements, ID3D11InputLayout ** ppd3dVertexLayout)
{
	HRESULT hResult;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob *pd3dShaderBlob = NULL, *pd3dErrorBlob = NULL;

	if (SUCCEEDED(hResult = D3DX11CompileFromFile(pszFileName,
		NULL, NULL, pszShaderName, pszShaderModel, dwShaderFlags, 0,
		NULL, &pd3dShaderBlob, &pd3dErrorBlob, NULL)))
	{
		pd3dDevice->CreateVertexShader(pd3dShaderBlob->GetBufferPointer(),
			pd3dShaderBlob->GetBufferSize(), NULL, ppd3dVertexShader);
		pd3dDevice->CreateInputLayout(pd3dInputLayout, nElements,
			pd3dShaderBlob->GetBufferPointer(), pd3dShaderBlob->GetBufferSize(),
			ppd3dVertexLayout);
		pd3dShaderBlob->Release();
	}
	else
	{
		MessageBox(NULL, L"Shader Code Error!", L"Error_VS", MB_ICONERROR);
		exit(1);
	}
}

void CShader::CreateGeometryShaderFromFile(ID3D11Device * pd3dDevice, WCHAR * pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderModel, ID3D11GeometryShader ** ppd3dGeometryShader)
{
	HRESULT hResult;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob *pd3dGeometryShaderBlob = NULL, *pd3dErrorBlob = NULL;
	if (SUCCEEDED(hResult = D3DX11CompileFromFile(pszFileName, NULL, NULL, pszShaderName, pszShaderModel,
		dwShaderFlags, 0, NULL, &pd3dGeometryShaderBlob, &pd3dErrorBlob, NULL)))
	{
		pd3dDevice->CreateGeometryShader(pd3dGeometryShaderBlob->GetBufferPointer(), pd3dGeometryShaderBlob->GetBufferSize(), NULL, ppd3dGeometryShader);
		pd3dGeometryShaderBlob->Release();
	}
	else
	{
		MessageBox(NULL, L"Shader Code Error!", L"Error_GS", MB_ICONERROR);
		exit(1);
	}
}

void CShader::CreatePixelShaderFromFile(ID3D11Device * pd3dDevice, WCHAR * pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderModel, ID3D11PixelShader ** ppd3dPixelShader)
{
	HRESULT hResult;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined(DEBUG) || defined(_DEBUG)
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob *pd3dShaderBlob = NULL, *pd3dErrorBlob = NULL;

	if (SUCCEEDED(hResult = D3DX11CompileFromFile(pszFileName,
		NULL, NULL, pszShaderName, pszShaderModel, dwShaderFlags, 0,
		NULL, &pd3dShaderBlob, &pd3dErrorBlob, NULL)))
	{
		pd3dDevice->CreatePixelShader(pd3dShaderBlob->GetBufferPointer(),
			pd3dShaderBlob->GetBufferSize(), NULL, ppd3dPixelShader);
		pd3dShaderBlob->Release();
	}
	else
	{
		MessageBox(NULL, L"Shader Code Error!", L"Error_PS", MB_ICONERROR);
		exit(1);
	}

}

void CShader::CreateShader(ID3D11Device * pd3dDevice)
{
	
}

void CShader::CreateShaderVariables(ID3D11Device * pd3dDevice)
{
	// 월드 변환 행렬을 위한 상수 버퍼를 생성한다.
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VS_CB_WORLD_MATRIX);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pd3dDevice->CreateBuffer(&bd, NULL, &m_pd3dcbWorldMatrix);
}

void CShader::ReleaseShaderVariables()
{
	// 월드 변환 행렬을 위한 상수 버퍼를 반환한다.
	if (m_pd3dcbWorldMatrix)
		m_pd3dcbWorldMatrix->Release();
}

void CShader::UpdateShaderVariable(ID3D11DeviceContext * pd3dDeviceContext, XMMATRIX pd3dxmtxWorld)
{
	// 월드 변환 행렬을 상수 버퍼에 복사한다.
	D3D11_MAPPED_SUBRESOURCE d3dMappedResource;
	pd3dDeviceContext->Map(m_pd3dcbWorldMatrix, 0, D3D11_MAP_WRITE_DISCARD, 0,
		&d3dMappedResource);
	VS_CB_WORLD_MATRIX *pcbWorldMatrix = (VS_CB_WORLD_MATRIX*)
		d3dMappedResource.pData;
	XMStoreFloat4x4(&pcbWorldMatrix->m_d3dxmtxWorld, XMMatrixTranspose(pd3dxmtxWorld));
	pd3dDeviceContext->Unmap(m_pd3dcbWorldMatrix, 0);

	// 상수 버퍼를 디바이스 슬롯(VS_SLOT_WORLD_MATRIX)에 연결한다.
	pd3dDeviceContext->VSSetConstantBuffers(VS_SLOT_WORLD_MATRIX, 1,
		&m_pd3dcbWorldMatrix);
}

void CShader::BuildObjects(ID3D11Device * pd3dDevice)
{
}

void CShader::ReleaseObjects()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) if (m_ppObjects[j]) delete m_ppObjects[j];
		delete[] m_ppObjects;
	}

}

void CShader::AnimateObjects(float fTimeElapsed)
{
	for (int j = 0; j < m_nObjects; j++)
	{
		m_ppObjects[j]->Animate(fTimeElapsed);
	}
}

void CShader::OnPrepareRender(ID3D11DeviceContext * pd3dDeviceContext)
{
	pd3dDeviceContext->IASetInputLayout(m_pd3dVertexLayout);
	pd3dDeviceContext->VSSetShader(m_pd3dVertexShader, NULL, 0);
	pd3dDeviceContext->GSSetShader(m_pd3dGeometryShader, NULL, 0);
	pd3dDeviceContext->PSSetShader(m_pd3dPixelShader, NULL, 0);
}

void CShader::Render(ID3D11DeviceContext * pd3dDeviceContext, shared_ptr<CCamera>pCamera)
{
	OnPrepareRender(pd3dDeviceContext);

	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j])
		{
			//카메라의 절두체에 포함되는 객체들만을 렌더링한다. 
			if (m_ppObjects[j]->IsVisible(pCamera))
			{
				m_ppObjects[j]->UpdateTransform(NULL);
				m_ppObjects[j]->Render(pd3dDeviceContext, pCamera);
			}
		}
	}

}

void CShader::AddObject(CGameObject * pGameObject)
{
	m_ppObjects[m_nIndexToAdd++] = pGameObject;
	if (pGameObject) pGameObject->AddRef();
}

CTexturedShader::CTexturedShader(int nObjects)
	:CShader(nObjects)
{
}

CTexturedShader::~CTexturedShader()
{
}

void CTexturedShader::CreateShader(ID3D11Device * pd3dDevice)
{
	D3D11_INPUT_ELEMENT_DESC d3dInputElements[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT nElements = ARRAYSIZE(d3dInputElements);
	CreateVertexShaderFromFile(pd3dDevice, L"Effect.fx", "VSTexturedColor", "vs_5_0", &m_pd3dVertexShader, d3dInputElements, nElements, &m_pd3dVertexLayout);
	CreatePixelShaderFromFile(pd3dDevice, L"Effect.fx", "PSTexturedColor", "ps_5_0", &m_pd3dPixelShader);
}

CDetailTexturedShader::CDetailTexturedShader(int nObjects)
	:CTexturedShader(nObjects)
{
}

CDetailTexturedShader::~CDetailTexturedShader()
{
}

void CDetailTexturedShader::CreateShader(ID3D11Device * pd3dDevice)
{
	D3D11_INPUT_ELEMENT_DESC d3dInputElements[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 2, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT nElements = ARRAYSIZE(d3dInputElements);
	CreateVertexShaderFromFile(pd3dDevice, L"Effect.fx", "VSDetailTexturedColor", "vs_5_0", &m_pd3dVertexShader, d3dInputElements, nElements, &m_pd3dVertexLayout);
	CreatePixelShaderFromFile(pd3dDevice, L"Effect.fx", "PSDetailTexturedColor", "ps_5_0", &m_pd3dPixelShader);
}

CIlluminatedShader::CIlluminatedShader(int nObjects)
	:CShader(nObjects)
{
}

CIlluminatedShader::~CIlluminatedShader()
{
}

void CIlluminatedShader::CreateShader(ID3D11Device * pd3dDevice)
{
	D3D11_INPUT_ELEMENT_DESC d3dInputElements[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT nElements = ARRAYSIZE(d3dInputElements);
	CreateVertexShaderFromFile(pd3dDevice, L"Effect.fx", "VSLightingColor", "vs_5_0", &m_pd3dVertexShader, d3dInputElements, nElements, &m_pd3dVertexLayout);
	CreatePixelShaderFromFile(pd3dDevice, L"Effect.fx", "PSLightingColor", "ps_5_0", &m_pd3dPixelShader);
}

void CIlluminatedShader::CreateShaderVariables(ID3D11Device * pd3dDevice)
{
	D3D11_BUFFER_DESC d3dBufferDesc;
	ZeroMemory(&d3dBufferDesc, sizeof(D3D11_BUFFER_DESC));
	d3dBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	d3dBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	d3dBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	d3dBufferDesc.ByteWidth = sizeof(MATERIAL);
	pd3dDevice->CreateBuffer(&d3dBufferDesc, NULL, &m_pd3dcbMaterial);
}

void CIlluminatedShader::ReleaseShaderVariables()
{
	if (m_pd3dcbMaterial) m_pd3dcbMaterial->Release();
}

void CIlluminatedShader::UpdateShaderVariable(ID3D11DeviceContext * pd3dDeviceContext, MATERIAL * pMaterial)
{
	D3D11_MAPPED_SUBRESOURCE d3dMappedResource;
	pd3dDeviceContext->Map(m_pd3dcbMaterial, 0, D3D11_MAP_WRITE_DISCARD, 0, &d3dMappedResource);
	MATERIAL *pcbMaterial = (MATERIAL *)d3dMappedResource.pData;
	memcpy(pcbMaterial, pMaterial, sizeof(MATERIAL));
	pd3dDeviceContext->Unmap(m_pd3dcbMaterial, 0);
	pd3dDeviceContext->PSSetConstantBuffers(PS_SLOT_MATERIAL, 1, &m_pd3dcbMaterial);
}

CTexturedIlluminatedShader::CTexturedIlluminatedShader(int nObjects)
	:CIlluminatedShader(nObjects)
{
}

CTexturedIlluminatedShader::~CTexturedIlluminatedShader()
{
}

void CTexturedIlluminatedShader::CreateShader(ID3D11Device * pd3dDevice)
{
	D3D11_INPUT_ELEMENT_DESC d3dInputElements[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 2, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT nElements = ARRAYSIZE(d3dInputElements);
	CreateVertexShaderFromFile(pd3dDevice, L"Effect.fx", "VSTexturedLightingColor", "vs_5_0", &m_pd3dVertexShader, d3dInputElements, nElements, &m_pd3dVertexLayout);
	CreatePixelShaderFromFile(pd3dDevice, L"Effect.fx", "PSTexturedLightingColor", "ps_5_0", &m_pd3dPixelShader);
}

CDetailTexturedIlluminatedShader::CDetailTexturedIlluminatedShader(int nObjects)
	:CTexturedIlluminatedShader(nObjects)
{
}

CDetailTexturedIlluminatedShader::~CDetailTexturedIlluminatedShader()
{
}

void CDetailTexturedIlluminatedShader::CreateShader(ID3D11Device * pd3dDevice)
{
	D3D11_INPUT_ELEMENT_DESC d3dInputElements[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 2, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 3, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT nElements = ARRAYSIZE(d3dInputElements);
	CreateVertexShaderFromFile(pd3dDevice, L"Effect.fx", "VSDetailTexturedLightingColor", "vs_5_0", &m_pd3dVertexShader, d3dInputElements, nElements, &m_pd3dVertexLayout);
	CreatePixelShaderFromFile(pd3dDevice, L"Effect.fx", "PSDetailTexturedLightingColor", "ps_5_0", &m_pd3dPixelShader);

}

CDiffusedShader::CDiffusedShader(int nObjects)
{
}

CDiffusedShader::~CDiffusedShader()
{
}

void CDiffusedShader::CreateShader(ID3D11Device * pd3dDevice)
{
	D3D11_INPUT_ELEMENT_DESC d3dInputLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
		0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,
		0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	UINT nElements = ARRAYSIZE(d3dInputLayout);

	CreateVertexShaderFromFile(pd3dDevice, L"Effect.fx", "VS", "vs_5_0",
		&m_pd3dVertexShader, d3dInputLayout, nElements, &m_pd3dVertexLayout);

	CreatePixelShaderFromFile(pd3dDevice, L"Effect.fx", "PS", "ps_5_0",
		&m_pd3dPixelShader);

}

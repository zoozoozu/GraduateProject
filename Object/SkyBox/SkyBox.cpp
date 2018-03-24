#include "stdafx.h"
#include "Object/SkyBox/SkyBox.h"
#include "Mesh/SkyBoxMesh/SkyBoxMesh.h"
#include "Shader/Shader.h"

CSkyBox::CSkyBox(ID3D11Device *pd3dDevice) : CGameObject(1)
{
	CSkyBoxMesh *pSkyBoxMesh = new CSkyBoxMesh(pd3dDevice, 20.0f, 20.0f, 20.0f);
	SetMesh(pSkyBoxMesh, 0);
}

CSkyBox::~CSkyBox()
{
}

void CSkyBox::Render(ID3D11DeviceContext *pd3dDeviceContext, CCamera *pCamera)
{
	//��ī�� �ڽ� ��ü�� ��ġ�� ī�޶��� ��ġ�� �����Ѵ�.
	XMFLOAT3 d3dxvCameraPos = pCamera->GetPosition();
	SetPosition(d3dxvCameraPos.x, d3dxvCameraPos.y, d3dxvCameraPos.z);
	
	CGameObject::UpdateTransform(NULL);
	CShader::UpdateShaderVariable(pd3dDeviceContext, XMLoadFloat4x4(&m_xmf4x4World));

	//��ī�� �ڽ� �޽�(6���� �簢��)�� �������Ѵ�.
	if (m_ppMeshes && m_ppMeshes[0]) m_ppMeshes[0]->Render(pd3dDeviceContext);
}


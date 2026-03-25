#include "UStaticMeshComponent.h"
#include "../GameEngine.h"
#include "../SubSystem/CameraManager.h"


void UStaticMeshComponent::SetMeshAsset(const FStaticMeshAsset& asset)
{
	m_pMesh = asset.m_pMesh;
	MeshMaterials = asset.MeshMaterials;
	MeshTextures = asset.MeshTextures;
	NumberMaterials = asset.NumberMaterials;
	meshID = asset.id;

	D3DVERTEXELEMENT9 vertexElements[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};
	GameEngine::GetDevice()->CreateVertexDeclaration(vertexElements, &vertexDecl);

	LPD3DXBUFFER buffer = nullptr;
	D3DXCreateEffectFromFileA(GameEngine::GetDevice(), "2.fx", NULL, NULL, 0, NULL, &effect, &buffer);
	if (buffer)
	{
		OutputDebugStringA((char*)buffer->GetBufferPointer());
	}
}

void UStaticMeshComponent::Render()
{
	//环境+漫反射+高光
	static float angle = 0;
	angle += 0.01f;
	D3DXMATRIXA16 world;
	D3DXMatrixIdentity(&world);
	D3DXMatrixRotationY(&world,angle);
	D3DXMATRIXA16 v = CameraManager::GetInstance()->GetViewMatrix();
	D3DXMATRIXA16 mvp = world * v * CameraManager::GetInstance()->GetProjMatrix();

	effect->SetMatrix("WorldViewProj", &mvp);
	effect->SetMatrix("viewMatrix", &v);
	effect->SetFloat("angle",angle);

	D3DXVECTOR3 eye = CameraManager::GetInstance()->GetEyeDir();
	effect->SetVector("EyeDir", (D3DXVECTOR4*)(&eye));

	Update();
	if (Visible)
	{
		for (int i = 0; i < NumberMaterials; i++)
		{
			effect->SetTexture("myTexture", MeshTextures[i]);
			effect->SetTechnique("MyEffect01");
			UINT pass = 0;
			effect->Begin(&pass, 0);
			for (int i = 0; i < pass; i++)
			{
				effect->BeginPass(i);
				m_pMesh->DrawSubset(i);
				effect->EndPass();
			}
			effect->End();
		}
	}
}

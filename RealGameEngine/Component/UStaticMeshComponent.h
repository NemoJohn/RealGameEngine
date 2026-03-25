#pragma once

#include "USceneComponent.h"

class UStaticMeshComponent :public USceneComponent
{
public:
	void SetMeshAsset(const FStaticMeshAsset& asset);
	virtual void Render();

	string meshID;
protected:
	LPD3DXMESH m_pMesh = nullptr;
	vector<D3DMATERIAL9>	   MeshMaterials;
	vector<LPDIRECT3DTEXTURE9> MeshTextures;
	DWORD NumberMaterials = 0;

private:
	LPD3DXEFFECT effect = nullptr;
	LPDIRECT3DVERTEXDECLARATION9 vertexDecl = nullptr;
};


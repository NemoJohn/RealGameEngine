#pragma once

#include <d3dx9.h>


class BasePrimitive
{
public:
	BasePrimitive();
	~BasePrimitive();
	void CreateVertex();
	void OnRender();

protected:


private:
	LPDIRECT3DVERTEXBUFFER9 m_pVB = NULL;
	LPDIRECT3DDEVICE9 pDevice = nullptr;

	struct CustomVertex
	{
		//法线的主要作用 光照中的漫反射与镜面反射
		float x, y, z;
		float nx, ny, nz;
		float u, v;
		const static DWORD FVF = D3DFVF_XYZ |D3DFVF_NORMAL| D3DFVF_TEX1;
	};

	//每个小格的宽高
	float w = 0.1f;
	float h = 0.1f;
	float col = 40;
	float raw = 40;

	LPD3DXEFFECT effect = nullptr;
	LPDIRECT3DVERTEXDECLARATION9 vertexDecl = nullptr;
	
};


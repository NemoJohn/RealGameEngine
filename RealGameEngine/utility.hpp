#pragma once

#include <string>
#include <vector>
#include <map>
using namespace std;

#include <d3dx9.h>
#include <windows.h>


struct FRotator
{
	float roll = 0;
	float pitch = 0;
	float yaw = 0;
	FRotator operator-(FRotator _other)
	{
		FRotator r;
		r.pitch = pitch - _other.pitch;
		r.yaw = yaw - _other.yaw;
		r.roll = roll - _other.roll;
		return r;
	}
};

struct FTextureObject
{
	string id = "";
	string name = "";
	LPDIRECT3DTEXTURE9 texture = nullptr;
	UINT w = 0;
	UINT h = 0;
	string path = "";
};

struct FStaticMeshAsset
{
	string id = "";
	string name = "";
	LPD3DXMESH m_pMesh = nullptr;
	vector<D3DMATERIAL9>	   MeshMaterials;
	vector<LPDIRECT3DTEXTURE9> MeshTextures;
	DWORD NumberMaterials = 0;
};

enum MouseType
{
	LButtonType,
	RButtonType,
};

template<typename T>
T* CreateDefaultSubobject(string _name = "")
{
	T* p = new T;
	p->name = _name;
	return p;
}




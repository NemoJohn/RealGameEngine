#include "StaticMeshCache.h"
#include "../GameEngine.h"

void StaticMeshCache::Init()
{
	//分析XML，数据加载到map中
	TiXmlDocument doc("Resource/Mesh/StaticMesh.xml");
	if (!doc.LoadFile())
	{
		MessageBox(nullptr, L"警告", L"静态网格数据缓冲加载失败", MB_OK);
	}
	TiXmlElement* root = doc.FirstChildElement("StaticMesh");
	TiXmlElement* child = root->FirstChildElement("child");

	for (; child != nullptr; child = child->NextSiblingElement("child"))
	{
		
		FStaticMeshAsset asset;
		asset.id = child->Attribute("id");
        asset.name = child->Attribute("name");
		string meshName = child->Attribute("path");

        //原本模型的贴图路径的修复
        string path = meshName.substr(0, meshName.find_last_of("/"));
        path += "/";

        LPD3DXBUFFER buffer;
        LPD3DXBUFFER adj;
        D3DXLoadMeshFromXA(meshName.c_str(), D3DXMESH_SYSTEMMEM,
            GameEngine::GetDevice(), &adj,
            &buffer, NULL, &asset.NumberMaterials,
            &asset.m_pMesh);

        LPD3DXMESH tempMesh = nullptr;
        asset.m_pMesh->CloneMeshFVF(D3DXMESH_SYSTEMMEM, asset.m_pMesh->GetFVF() | D3DFVF_NORMAL, GameEngine::GetDevice(), &tempMesh);


        D3DXComputeNormals(tempMesh, (DWORD*)adj->GetBufferPointer());
        D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)buffer->GetBufferPointer();

        for (DWORD i = 0; i < asset.NumberMaterials; i++)
        {
            asset.MeshMaterials.push_back(d3dxMaterials[i].MatD3D);

            LPDIRECT3DTEXTURE9 texture = nullptr;
            string localPath = path;
            localPath += d3dxMaterials[i].pTextureFilename;
            path += d3dxMaterials[i].pTextureFilename;
            D3DXCreateTextureFromFileA(GameEngine::GetDevice(), localPath.c_str(), &texture);
            asset.MeshTextures.push_back(texture);
        }
        adj->Release();
        buffer->Release();
        asset.m_pMesh->Release();
        asset.m_pMesh = tempMesh;

        allStaticMesh.insert(pair<string, FStaticMeshAsset>(asset.id, asset));
	}
}

FStaticMeshAsset StaticMeshCache::FindStaticMeshAssetByID(string id)
{
    if (allStaticMesh.find(id) != allStaticMesh.end())
    {
        return allStaticMesh[id];
    }
    return FStaticMeshAsset();
}

#include "TextureCache.h"
#include "../GameEngine.h"

void TextureCache::Init()
{
	//分析XML，数据加载到map中
	TiXmlDocument doc("Resource/Texture/TextureCache.xml");
	if (!doc.LoadFile())
	{
		MessageBox(nullptr, L"警告", L"纹理缓冲加载失败", MB_OK);
	}
	TiXmlElement* root = doc.FirstChildElement("TextureCache");
	TiXmlElement* child = root->FirstChildElement("TextureObject");

	for (; child != nullptr; child = child->NextSiblingElement("TextureObject"))
	{
		FTextureObject object;
		object.id = child->Attribute("id");
		object.name = child->Attribute("name");
		object.path = child->Attribute("path");
		D3DXIMAGE_INFO info;
		
		D3DXCreateTextureFromFileExA(GameEngine::GetDevice(), object.path.c_str(),
			D3DX_FROM_FILE, D3DX_FROM_FILE,
			0, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
			D3DX_FILTER_BOX, D3DX_FILTER_BOX, 0,
			&info, nullptr, &object.texture);
		object.w = info.Width;
		object.h = info.Height;
		//allTextures[object.id] = object;
		allTextures.insert(pair<string,FTextureObject>(object.id,object));
	}
	
}

LPDIRECT3DTEXTURE9 TextureCache::GetTextureByID(string id)
{
	if (allTextures.find(id) != allTextures.end())
	{
		return allTextures[id].texture;
	}
	return nullptr;
}

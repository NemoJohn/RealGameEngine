#pragma once

#include "TSingleton.h"
#include "../xml/tinyxml.h"
#include "../utility.hpp"

class TextureCache : public TSingleton<TextureCache>
{
public:
	void Init();

	//根据id name 路径引用获取当前纹理
	LPDIRECT3DTEXTURE9 GetTextureByID(string id);

private:
	map<string, FTextureObject> allTextures;
};


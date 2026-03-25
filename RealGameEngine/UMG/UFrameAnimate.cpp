#include "UFrameAnimate.h"
#include "../GameEngine.h"
#include "../SubSystem/TextureCache.h"

void UFrameAnimate::CreateFrameAnimate(string _id, float w, float h, int _nFrames, float _fps)
{
	TextureID = _id;
	CellWidth = w;
	CellHeight = h;
	nFrames = _nFrames;
	fps = _fps;
}

void UFrameAnimate::Init()
{
	D3DXCreateSprite(GameEngine::GetDevice(), &spr);
}

void UFrameAnimate::Tick(float dt)
{
	if (GetAsyncKeyState('S'))
	{
		SetRect(&size, 0 + curFrame * CellWidth, 0, CellWidth + curFrame * CellWidth, CellHeight);
	}
	if (GetAsyncKeyState('A'))
	{
		SetRect(&size, 0 + curFrame * CellWidth, CellHeight, CellWidth + curFrame * CellWidth, 2*CellHeight);
	}
	if (GetAsyncKeyState('D'))
	{
		SetRect(&size, 0 + curFrame * CellWidth, 2 * CellHeight, CellWidth + curFrame * CellWidth, 3*CellHeight);
	}
	if (GetAsyncKeyState('W'))
	{
		SetRect(&size, 0 + curFrame * CellWidth, 3 * CellHeight, CellWidth + curFrame * CellWidth, 4*CellHeight);
	}
	
	//dt可以累积 累积的值大于1/FPS了就播放一次
	ct += dt;
	if (ct > 1.0f / fps)
	{
		curFrame++;
		ct = 0;
	}
	if (curFrame > nFrames-1)
	{
		curFrame = 0;
	}
}

void UFrameAnimate::Render()
{
	spr->Begin(D3DXSPRITE_ALPHABLEND);
	spr->Draw(TextureCache::GetInstance()->GetTextureByID(TextureID), &size, &center, &location, 0xFFFFFFFF);
	spr->End();
}

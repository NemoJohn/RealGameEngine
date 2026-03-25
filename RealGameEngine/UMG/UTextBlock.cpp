#include "UTextBlock.h"
#include "../GameEngine.h"

UTextBlock::UTextBlock()
{
	ZeroMemory(&FrameRect, sizeof(FrameRect));
}

void UTextBlock::Init(float FontWidth, float FontHeight)
{
	D3DXCreateFont(GameEngine::GetDevice(), 20, 10, 3, 0, false, 0, 0, 0, 0, L"宋体", &font);
	FontFrameWidth = FontWidth;
	FontFrameHeight = FontHeight;
}

void UTextBlock::Render()
{
	Update();
	SetRect(&FrameRect, location.x, location.y, location.x + FontFrameWidth, location.y + FontFrameHeight);
	font->DrawTextW(nullptr, L"今天天气不错呀", 7, &FrameRect, DT_LEFT|DT_WORDBREAK, 0XFFFF0000);
}

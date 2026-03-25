#include "UButton.h"
#include "../GameEngine.h"
#include "../SubSystem/TextureCache.h"

void UButton::Init()
{
	D3DXCreateSprite(GameEngine::GetDevice(), &spr);
}

void UButton::Render()
{
	spr->Begin(D3DXSPRITE_ALPHABLEND);
	spr->Draw(TextureCache::GetInstance()->GetTextureByID("1001"), &size, &center, &location, 0xFFFFFFFF);
	spr->End();

	if (uniqueChild)
	{
		uniqueChild->Render();
	}
}


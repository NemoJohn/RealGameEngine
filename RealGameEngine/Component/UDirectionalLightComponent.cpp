#include "UDirectionalLightComponent.h"

UDirectionalLightComponent::UDirectionalLightComponent()
{
	light.Type = D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL;
}

void UDirectionalLightComponent::SetDirectional(D3DXVECTOR3 dir)
{
	D3DXVec3Normalize(&dir, &dir);
	light.Direction = dir;
}

void UDirectionalLightComponent::SetDirectional(float x, float y, float z)
{
	D3DXVECTOR3 dir(x,y,z);
	D3DXVec3Normalize(&dir, &dir);
	light.Direction = dir;
}

D3DXVECTOR3 UDirectionalLightComponent::GetDirectional() const
{
	return light.Direction;
}

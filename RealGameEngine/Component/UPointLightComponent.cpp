#include "UPointLightComponent.h"

UPointLightComponent::UPointLightComponent()
{
	light.Type = D3DLIGHTTYPE::D3DLIGHT_POINT;
}

void UPointLightComponent::SetLightLocation(D3DXVECTOR3 location)
{
	light.Position = location;
}

void UPointLightComponent::SetLightLocation(float x, float y, float z)
{
	light.Position.x = x;
	light.Position.y = y;
	light.Position.z = z;
}

D3DXVECTOR3 UPointLightComponent::GetLightLocation() const
{
	return light.Position;
}

void UPointLightComponent::SetLightRange(float _range)
{
	light.Range = _range;
}

float UPointLightComponent::GetLightRange() const
{
	return light.Range;
}

void UPointLightComponent::SetLightFallOff(float falloff)
{
	light.Falloff = falloff;
}

float UPointLightComponent::GetLightFallOff() const
{
	return light.Falloff;
}

#include "USpotLightComponent.h"

USpotLightComponent::USpotLightComponent()
{
	light.Type = D3DLIGHTTYPE::D3DLIGHT_SPOT;
}

void USpotLightComponent::SetDirectional(D3DXVECTOR3 dir)
{
	D3DXVec3Normalize(&dir, &dir);
	light.Direction = dir;
}

void USpotLightComponent::SetDirectional(float x, float y, float z)
{
	D3DXVECTOR3 dir(x, y, z);
	D3DXVec3Normalize(&dir, &dir);
	light.Direction = dir;
}

D3DXVECTOR3 USpotLightComponent::GetDirectional() const
{
	return light.Direction;
}

void USpotLightComponent::SetInnerAngle(float angle)
{
	light.Theta = angle * (D3DX_PI / 180.0f);
}

float USpotLightComponent::GetInnerAngle() const
{
	return light.Theta/(D3DX_PI / 180.0f);
}

void USpotLightComponent::SetOuterAngle(float angle)
{
	light.Phi = angle * (D3DX_PI / 180.0f);
}

float USpotLightComponent::GetOuterAngle() const
{
	return light.Phi / (D3DX_PI / 180.0f);
}

void USpotLightComponent::SetConstantAttenuation(float Attenuation)
{
	light.Attenuation0 = Attenuation;
}

float USpotLightComponent::GetConstantAttenuation() const
{
	return light.Attenuation0;
}

void USpotLightComponent::SetLinearAttenuation(float Attenuation)
{
	light.Attenuation1 = Attenuation;
}

float USpotLightComponent::GetLinearAttenuation() const
{
	return light.Attenuation1;
}

void USpotLightComponent::SetQuadraticAttenuation(float Attenuation)
{
	light.Attenuation2 = Attenuation;
}

float USpotLightComponent::GetQuadraticAttenuation() const
{
	return light.Attenuation2;
}

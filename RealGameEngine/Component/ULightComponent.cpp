#include "ULightComponent.h"
#include "../SubSystem/LightManager.h"

ULightComponent::ULightComponent()
{
	ZeroMemory(&light,sizeof(light));
	LightManager::GetInstance()->AddLight(this);
}

ULightComponent::~ULightComponent()
{
	LightManager::GetInstance()->RemoveLight(LightID);
}

void ULightComponent::SetAmbientColor(float r, float g, float b, float a)
{
	light.Ambient.r = r;
	light.Ambient.g = g;
	light.Ambient.b = b;
	light.Ambient.a = a;
}

void ULightComponent::SetAmbientColor(D3DCOLORVALUE color)
{
	light.Ambient = color;
}

D3DCOLORVALUE ULightComponent::GetAmbientColor() const
{
	return light.Ambient;
}

void ULightComponent::SetDiffuseColor(float r, float g, float b, float a)
{
	light.Diffuse.r = r;
	light.Diffuse.g = g;
	light.Diffuse.b = b;
	light.Diffuse.a = a;
}

void ULightComponent::SetDiffuseColor(D3DCOLORVALUE color)
{
	light.Diffuse = color;
}

D3DCOLORVALUE ULightComponent::GetDiffuseColor() const
{
	return light.Diffuse;
}

void ULightComponent::SetSpecularColor(float r, float g, float b, float a)
{
	light.Specular.r = r;
	light.Specular.g = g;
	light.Specular.b = b;
	light.Specular.a = a;
}

void ULightComponent::SetSpecularColor(D3DCOLORVALUE color)
{
	light.Specular = color;
}

D3DCOLORVALUE ULightComponent::GetSpecularColor() const
{
	return light.Specular;
}

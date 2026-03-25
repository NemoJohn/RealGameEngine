#pragma once

#include "USceneComponent.h"

class ULightComponent :
    public USceneComponent
{
public:
    ULightComponent();
    ~ULightComponent();

    //颜色修改是共有的
    void SetAmbientColor(float r, float g, float b, float a = 1);
    void SetAmbientColor(D3DCOLORVALUE color);
    D3DCOLORVALUE GetAmbientColor()const;

    void SetDiffuseColor(float r, float g, float b, float a = 1);
    void SetDiffuseColor(D3DCOLORVALUE color);
    D3DCOLORVALUE GetDiffuseColor()const;

    void SetSpecularColor(float r, float g, float b, float a = 1);
    void SetSpecularColor(D3DCOLORVALUE color);
    D3DCOLORVALUE GetSpecularColor()const;

protected:
    D3DLIGHT9 light;

private:
    int LightID = 0;
    friend class LightManager;
};


#pragma once
#include "UPointLightComponent.h"
class USpotLightComponent :
    public UPointLightComponent
{
public:
    USpotLightComponent();

    void SetDirectional(D3DXVECTOR3 dir);
    void SetDirectional(float x, float y, float z);
    D3DXVECTOR3 GetDirectional()const;

    void SetInnerAngle(float angle);
    float GetInnerAngle()const;
    void SetOuterAngle(float angle);
    float GetOuterAngle()const;

    void SetConstantAttenuation(float Attenuation);
    float GetConstantAttenuation()const;
    void SetLinearAttenuation(float Attenuation);
    float GetLinearAttenuation()const;
    void SetQuadraticAttenuation(float Attenuation);
    float GetQuadraticAttenuation()const;

protected:

private:

};


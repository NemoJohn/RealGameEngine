#pragma once
#include "ULightComponent.h"
class UPointLightComponent :
    public ULightComponent
{
public:
    UPointLightComponent();

    void SetLightLocation(D3DXVECTOR3 location);
    void SetLightLocation(float x, float y, float z);
    D3DXVECTOR3 GetLightLocation()const;

    void SetLightRange(float _range);
    float GetLightRange()const;
    void SetLightFallOff(float falloff);
    float GetLightFallOff()const;

protected:

private:

};


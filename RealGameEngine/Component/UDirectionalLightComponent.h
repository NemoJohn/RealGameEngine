#pragma once
#include "ULightComponent.h"

class UDirectionalLightComponent :
    public ULightComponent
{
public:
    UDirectionalLightComponent();

    void SetDirectional(D3DXVECTOR3 dir);
    void SetDirectional(float x, float y, float z);
    D3DXVECTOR3 GetDirectional()const;
protected:

private:

};


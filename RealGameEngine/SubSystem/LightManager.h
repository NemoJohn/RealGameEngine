#pragma once
#include "TSingleton.h"
#include "../utility.hpp"
#include "../Component/ULightComponent.h"

class LightManager :
    public TSingleton<LightManager>
{
public:
    void AddLight(ULightComponent* lightRef);
    void RemoveLight(int LightID);
    void Update();
private:
    vector<ULightComponent*> allLights;
};


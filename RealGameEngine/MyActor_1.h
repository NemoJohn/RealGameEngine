#pragma once
#include "AActor.h"
class MyActor_1 :
    public AActor
{
public:
    MyActor_1();

private:
    class UStaticMeshComponent* comp = nullptr;
    class UPointLightComponent* light = nullptr;
    class UCameraComponent* camera1 = nullptr;

};


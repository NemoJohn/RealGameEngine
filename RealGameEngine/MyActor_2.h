#pragma once
#include "AActor.h"
class MyActor_2 :
    public AActor
{
public:
    MyActor_2();
private:
    class UStaticMeshComponent* comp1 = nullptr;
};


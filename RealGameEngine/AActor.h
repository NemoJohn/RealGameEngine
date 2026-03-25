#pragma once

#include <vector>
using namespace std;

#include "UObject.h"

class AActor :
    public UObject
{
public:
    AActor();
    virtual ~AActor();

    virtual void BeginPlay();
    virtual void Tick(float dt);
    virtual void Update();
    virtual void Render();
    virtual void EndPlay();

    void SetActorLocation(float x, float y, float z);
    D3DXVECTOR3 GetActorLocation()const;
    void SetActorRotation(float pitch,float yaw,float roll);
    FRotator GetActorRotation()const;
    void SetActorScaling(float sx, float sy, float sz);
    D3DXVECTOR3 GetActorScaling()const;

    void AddActorComponent(UObject* comp);
    void AddSceneComponent(UObject* comp);

protected:
    D3DXMATRIXA16 transfrom;
    D3DXMATRIXA16 location;
    D3DXMATRIXA16 rotation;
    D3DXMATRIXA16 scale;
    FRotator rotator;

    vector<UObject*> allActorComponents;
    vector<UObject*> allSceneComponents;

private:
    friend class WorldContext;
};


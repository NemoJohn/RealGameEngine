#pragma once
#include "UActorComponent.h"

//和actor相同的一套变换机制，但是多了属于自己的相对的变换
//绝对变换-相对与世界坐标系的
//相对变换-参照物它父
class USceneComponent :
    public UActorComponent
{
public:
    USceneComponent();

    void SetWorldLocation(float x, float y, float z);
    D3DXVECTOR3 GetWorldLocation()const;
    void SetWorldRotation(float pitch, float yaw, float roll);
    FRotator GetWorldRotation()const;
    void SetWorldScaling(float sx, float sy, float sz);
    D3DXVECTOR3 GetWorldScaling()const;

    virtual void SetupAttachment(UObject* _parent);
    virtual void Update();

    void SetRelativeLocation(float x, float y, float z);
    D3DXVECTOR3 GetRelativeLocation()const;
    void SetRelativeRotation(float pitch, float yaw, float roll);
    FRotator GetRelativeRotation()const;
    void SetRelativeScaling(float sx, float sy, float sz);
    D3DXVECTOR3 GetRelativeScaling()const;

    void SetVisible(bool visible);
    bool GetVisible()const;
protected:
    D3DXMATRIXA16 transfrom;
    D3DXMATRIXA16 location;
    D3DXMATRIXA16 rotation;
    D3DXMATRIXA16 scale;
    FRotator rotator;

    //相对坐标的值
    D3DXVECTOR3 RelativeLocation;
    FRotator    RelativeRotator;
    D3DXVECTOR3 RelativeScale;

    //是否可视
    bool Visible = true;

private:

};


#pragma once
#include "../UObject.h"

class UWidget :
    public UObject
{
public:
    UWidget();

    bool MouseCollision(int mx, int my);
    
    virtual void Update();
    virtual bool OnMouseButtonDown(MouseType _type);
    virtual bool OnMouseButtonUp(MouseType _type);

    void SetLocation(float x,float y);
    D3DXVECTOR3 GetLocation()const;
    void SetCenter(D3DXVECTOR3 _center);
    D3DXVECTOR3 GetCenter()const;
    void SetSize(float w, float h);
    RECT GetSize()const;

    void SetZOrder(float z);
    float GetZOrder()const;

    void AddToViewport(float zoder);

    void SetParent(UWidget* _parent);
    UWidget* GetParent()const;

    void SetRelativeLocation(float x, float y);
    D3DXVECTOR2 GetRelativeLocation()const;

protected:
    D3DXVECTOR3 location;
    D3DXVECTOR3 center;
    RECT size;

    //该控件的相对位置
    D3DXVECTOR2 RelativeLocation;

    //该控件的父级控件
    UWidget* parent = nullptr;
private:

};


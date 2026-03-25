#pragma once
#include "USceneComponent.h"

class UCameraComponent :
    public USceneComponent
{
public:
    UCameraComponent();
    void Update();

    void SetCameraPosition(D3DXVECTOR3 pos);
    D3DXVECTOR3 GetCameraPosition()const;
    void SetCameraLookAt(D3DXVECTOR3 look);
    D3DXVECTOR3 GetCameraLookAt()const;
    void SetCameraUpVec(D3DXVECTOR3 up);
    D3DXVECTOR3 GetCameraUpVec()const;

    void SetFovy(float _fovy);
    float GetFovy()const;
    void SetAspect(float _aspect);
    float GetAspect()const;
    void SetZNear(float zn);
    float GetZNear()const;
    void SetZFar(float zf);
    float GetZFar()const;

    void SetCameraActive(bool _active);
    bool GetCameraActive()const;
protected:
    D3DXVECTOR3 vEyePt;
    D3DXVECTOR3 vLookatPt;
    D3DXVECTOR3 vUpVec;
    float Fovy = D3DX_PI/4;
    float Aspect = 1;
    float ZNear = 1;
    float ZFar = 100;

    D3DXMATRIXA16 matView;
    D3DXMATRIXA16 matProj;

    bool IsActive = true;
private:

    friend class CameraManager;
};


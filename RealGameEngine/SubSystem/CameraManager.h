#pragma once
#include "TSingleton.h"
#include "../utility.hpp"
class CameraManager :
    public TSingleton<CameraManager>
{
public:
    void AddCamera(class UCameraComponent* comp);
    void Update();
    void SetCameraActive(class UCameraComponent* comp,bool _isactive);

	D3DXMATRIXA16 GetViewMatrix()const;
	D3DXMATRIXA16 GetProjMatrix()const;

    D3DXVECTOR3 GetEyeDir()const;

private:
    vector<class UCameraComponent*> allCamera;
};


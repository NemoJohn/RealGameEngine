#include "UCameraComponent.h"
#include "../GameEngine.h"
#include "../SubSystem/CameraManager.h"

UCameraComponent::UCameraComponent()
{
	CameraManager::GetInstance()->AddCamera(this);
	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);
	vEyePt = { 0,0,0 };
	vLookatPt = { 0,0,0 };
	vUpVec = { 0,1,0 };
}

void UCameraComponent::Update()
{
	if (IsActive)
	{
		D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
		GameEngine::GetDevice()->SetTransform(D3DTS_VIEW, &matView);
		D3DXMatrixPerspectiveFovLH(&matProj, Fovy, Aspect, ZNear, ZFar);
		GameEngine::GetDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
	}
}

void UCameraComponent::SetCameraPosition(D3DXVECTOR3 pos)
{
	vEyePt = pos;
}

D3DXVECTOR3 UCameraComponent::GetCameraPosition() const
{
	return vEyePt;
}

void UCameraComponent::SetCameraLookAt(D3DXVECTOR3 look)
{
	vLookatPt = look;
}

D3DXVECTOR3 UCameraComponent::GetCameraLookAt() const
{
	return vLookatPt;
}

void UCameraComponent::SetCameraUpVec(D3DXVECTOR3 up)
{
	vUpVec = up;
}

D3DXVECTOR3 UCameraComponent::GetCameraUpVec() const
{
	return vUpVec;
}

void UCameraComponent::SetFovy(float _fovy)
{
	Fovy = _fovy;
}

float UCameraComponent::GetFovy() const
{
	return Fovy;
}

void UCameraComponent::SetAspect(float _aspect)
{
	Aspect = _aspect;
}

float UCameraComponent::GetAspect() const
{
	return Aspect;
}

void UCameraComponent::SetZNear(float zn)
{
	ZNear = zn;
}

float UCameraComponent::GetZNear() const
{
	return ZNear;
}

void UCameraComponent::SetZFar(float zf)
{
	ZFar = zf;
}

float UCameraComponent::GetZFar() const
{
	return ZFar;
}

void UCameraComponent::SetCameraActive(bool _active)
{
	IsActive = _active;
	CameraManager::GetInstance()->SetCameraActive(this,_active);
}

bool UCameraComponent::GetCameraActive() const
{
	return IsActive;
}

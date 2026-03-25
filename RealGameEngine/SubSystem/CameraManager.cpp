#include "CameraManager.h"
#include "../Component/UCameraComponent.h"

void CameraManager::AddCamera(UCameraComponent* comp)
{
	for (int i = 0; i < allCamera.size(); i++)
	{
		if (allCamera[i]->IsActive == true)
		{
			comp->IsActive = false;
			
			break;
		}
		allCamera[i]->IsActive = false;
	}
	allCamera.push_back(comp);
}

void CameraManager::Update()
{
	for (int i = 0; i < allCamera.size(); i++)
	{
		if (allCamera[i]->IsActive)
		{
			allCamera[i]->Update();
		}
	}
}

void CameraManager::SetCameraActive(UCameraComponent* comp,bool _isactive)
{
	for (int i = 0; i < allCamera.size(); i++)
	{
		if (allCamera[i] != comp)
		{
			allCamera[i]->IsActive=false;
		}
	}
}

D3DXMATRIXA16 CameraManager::GetViewMatrix() const
{
	for (int i = 0; i < allCamera.size(); i++)
	{
		if (allCamera[i]->IsActive)
		{
			return allCamera[i]->matView;
		}
	}
}

D3DXMATRIXA16 CameraManager::GetProjMatrix() const
{
	for (int i = 0; i < allCamera.size(); i++)
	{
		if (allCamera[i]->IsActive)
		{
			return allCamera[i]->matProj;
		}
	}
}

D3DXVECTOR3 CameraManager::GetEyeDir() const
{
	for (int i = 0; i < allCamera.size(); i++)
	{
		if (allCamera[i]->IsActive)
		{
			return allCamera[i]->GetCameraLookAt()- allCamera[i]->GetCameraPosition();
		}
	}
}

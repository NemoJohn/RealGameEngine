#include "AActor.h"
#include "WorldContext.h"

AActor::AActor()
{
	WorldContext::GetInstance()->AddNode(this);
	D3DXMatrixIdentity(&transfrom);
	D3DXMatrixIdentity(&location);
	D3DXMatrixIdentity(&rotation);
	D3DXMatrixIdentity(&scale);
}

AActor::~AActor()
{
}

void AActor::BeginPlay()
{
}

void AActor::Tick(float dt)
{
	for (int i = 0; i < allActorComponents.size(); i++)
	{
		allActorComponents[i]->Tick(dt);
	}
	for (int i = 0; i < allSceneComponents.size(); i++)
	{
		allSceneComponents[i]->Tick(dt);
	}
}

//功能是更新矩阵，某些无绘制功能的东西，未必是更新矩阵
void AActor::Update()
{
	transfrom = scale * rotation * location;
	m_pDevice->SetTransform(D3DTS_WORLD,&transfrom);
}

void AActor::Render()
{
	for (int i = 0; i < allActorComponents.size(); i++)
	{
		allActorComponents[i]->Render();
	}
	for (int i = 0; i < allSceneComponents.size(); i++)
	{
		allSceneComponents[i]->Render();
	}
}

void AActor::EndPlay()
{
}

void AActor::SetActorLocation(float x, float y, float z)
{
	location._41 = x;
	location._42 = y;
	location._43 = z;


}

D3DXVECTOR3 AActor::GetActorLocation() const
{
	return D3DXVECTOR3(location._41, location._42, location._43);
}

void AActor::SetActorRotation(float pitch, float yaw, float roll)
{
	rotator.pitch = pitch;
	rotator.roll = roll;
	rotator.yaw = yaw;
	D3DXMatrixRotationYawPitchRoll(&rotation,(D3DX_PI/180.0f)*yaw, (D3DX_PI / 180.0f) * pitch, (D3DX_PI / 180.0f) * roll);
}

FRotator AActor::GetActorRotation() const
{
	return rotator;
}

void AActor::SetActorScaling(float sx, float sy, float sz)
{
	scale._11 = sx;
	scale._22 = sy;
	scale._33 = sz;
}

D3DXVECTOR3 AActor::GetActorScaling() const
{
	return D3DXVECTOR3(scale._11, scale._22, scale._33);
}

void AActor::AddActorComponent(UObject* comp)
{
	allActorComponents.push_back(comp);
}

void AActor::AddSceneComponent(UObject* comp)
{
	allSceneComponents.push_back(comp);
}

#include "USceneComponent.h"
#include "../AActor.h"

USceneComponent::USceneComponent()
{
	D3DXMatrixIdentity(&transfrom);
	D3DXMatrixIdentity(&location);
	D3DXMatrixIdentity(&rotation);
	D3DXMatrixIdentity(&scale);

	RelativeLocation = D3DXVECTOR3(0, 0, 0);
	RelativeScale = D3DXVECTOR3(1, 1, 1);
}

void USceneComponent::SetWorldLocation(float x, float y, float z)
{
	location._41 = x;
	location._42 = y;
	location._43 = z;
}

D3DXVECTOR3 USceneComponent::GetWorldLocation() const
{
	return D3DXVECTOR3(location._41, location._42, location._43);
}

void USceneComponent::SetWorldRotation(float pitch, float yaw, float roll)
{
	rotator.pitch = pitch;
	rotator.roll = roll;
	rotator.yaw = yaw;
	D3DXMatrixRotationYawPitchRoll(&rotation, (D3DX_PI / 180.0f) * yaw, (D3DX_PI / 180.0f) * pitch, (D3DX_PI / 180.0f) * roll);
}

FRotator USceneComponent::GetWorldRotation() const
{
	return rotator;
}

void USceneComponent::SetWorldScaling(float sx, float sy, float sz)
{
	scale._11 = sx;
	scale._22 = sy;
	scale._33 = sz;
}

D3DXVECTOR3 USceneComponent::GetWorldScaling() const
{
	return D3DXVECTOR3(scale._11, scale._22, scale._33);
}

void USceneComponent::SetupAttachment(UObject* _parent)
{
	parent = _parent;
	AActor* p = dynamic_cast<AActor*>(parent);
	p->AddSceneComponent(this);
}

void USceneComponent::Update()
{
	D3DXVECTOR3 m1 = dynamic_cast<AActor*>(GetOwning())->GetActorLocation();
	FRotator m2 = dynamic_cast<AActor*>(GetOwning())->GetActorRotation();
	D3DXVECTOR3 m3 = dynamic_cast<AActor*>(GetOwning())->GetActorScaling();
	location._41 = m1.x + RelativeLocation.x;
	location._42 = m1.y + RelativeLocation.y;
	location._43 = m1.z + RelativeLocation.z;

	rotator.pitch = m2.pitch + RelativeRotator.pitch;
	rotator.roll = m2.roll + RelativeRotator.roll;
	rotator.yaw = m2.yaw + RelativeRotator.yaw;
	D3DXMatrixRotationYawPitchRoll(&rotation, (D3DX_PI / 180.0f) * rotator.yaw,
		(D3DX_PI / 180.0f) * rotator.pitch,
		(D3DX_PI / 180.0f) * rotator.roll);

	scale._11 = m3.x * RelativeScale.x;
	scale._22 = m3.y * RelativeScale.y;
	scale._33 = m3.z * RelativeScale.z;

	transfrom = scale * rotation * location;
	m_pDevice->SetTransform(D3DTS_WORLD, &transfrom);
}

void USceneComponent::SetRelativeLocation(float x, float y, float z)
{
	RelativeLocation.x = x;
	RelativeLocation.y = y;
	RelativeLocation.z = z;
}

D3DXVECTOR3 USceneComponent::GetRelativeLocation()const
{
	return RelativeLocation;
}

void USceneComponent::SetRelativeRotation(float pitch, float yaw, float roll)
{
	RelativeRotator.pitch = pitch ;
	RelativeRotator.yaw = yaw;
	RelativeRotator.roll = roll;
}

FRotator USceneComponent::GetRelativeRotation()const
{
	return RelativeRotator;
}

void USceneComponent::SetRelativeScaling(float sx, float sy, float sz)
{
	RelativeScale.x = sx;
	RelativeScale.y = sy;
	RelativeScale.z = sz;
}

D3DXVECTOR3 USceneComponent::GetRelativeScaling() const
{
	return RelativeScale;
}

void USceneComponent::SetVisible(bool visible)
{
	Visible = visible;
}

bool USceneComponent::GetVisible() const
{
	return Visible;
}

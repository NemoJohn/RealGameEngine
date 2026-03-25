#include "UWidget.h"
#include "../SubSystem/UMGManager.h"

UWidget::UWidget()
{
	ZeroMemory(&location,sizeof(location));
	ZeroMemory(&center, sizeof(center));
	ZeroMemory(&size, sizeof(size));
	ZeroMemory(&RelativeLocation, sizeof(RelativeLocation));
}

bool UWidget::MouseCollision(int mx, int my)
{
	if (mx > location.x && my > location.y && mx < location.x + size.right && my < location.y + size.bottom)
	{
		return true;
	}
	return false;
}

void UWidget::Update()
{
	if (parent)
	{
		location.x = parent->GetLocation().x + RelativeLocation.x;
		location.y = parent->GetLocation().y + RelativeLocation.y;
	}
}

bool UWidget::OnMouseButtonDown(MouseType _type)
{
	return false;
}

bool UWidget::OnMouseButtonUp(MouseType _type)
{
	return false;
}

void UWidget::SetLocation(float x, float y)
{
	location.x = x;
	location.y = y;
}

D3DXVECTOR3 UWidget::GetLocation() const
{
	return location;
}

void UWidget::SetCenter(D3DXVECTOR3 _center)
{
	center = _center;
}

D3DXVECTOR3 UWidget::GetCenter() const
{
	return center;
}

void UWidget::SetSize(float w, float h)
{
	size.right = w;
	size.bottom = h;
}

RECT UWidget::GetSize() const
{
	return size;
}

void UWidget::SetZOrder(float zorder)
{
	location.z = 1.0f / zorder;
	UMGManager::GetInstance()->SortZOrder();
}

float UWidget::GetZOrder() const
{
	return location.z;
}

void UWidget::AddToViewport(float zoder)
{
	UMGManager::GetInstance()->AddWidget(this);
	SetZOrder(zoder);
}

void UWidget::SetParent(UWidget* _parent)
{
	parent = _parent;
}

UWidget* UWidget::GetParent() const
{
	return parent;
}

void UWidget::SetRelativeLocation(float x, float y)
{
	RelativeLocation.x = x;
	RelativeLocation.y = y;
}

D3DXVECTOR2 UWidget::GetRelativeLocation() const
{
	return RelativeLocation;
}

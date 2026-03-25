#include "UMGManager.h"

void UMGManager::AddWidget(UWidget* w)
{
	allWidgets.push_back(w);
}

void UMGManager::OnRender()
{
	for (int i = 0; i < allWidgets.size(); i++)
	{
		allWidgets[i]->Render();
	}
}

void UMGManager::SortZOrder()
{
	for (int i = 0; i < allWidgets.size(); i++)
	{
		for (int j = i; j < allWidgets.size(); j++)
		{
			if (allWidgets[i]->GetZOrder() < allWidgets[j]->GetZOrder())
			{
				UWidget* temp = allWidgets[i];
				allWidgets[i] = allWidgets[j];
				allWidgets[j] = temp;
			}
		}
	}
}

void UMGManager::ProcessMouseEvent(MouseType _type, int mx, int my, bool isPressed)
{
	if (isPressed)
	{
		for (int i = allWidgets.size() - 1; i >= 0; i--)
		{
			if (allWidgets[i]->MouseCollision(mx, my))
			{
				if (allWidgets[i]->OnMouseButtonDown(_type))
				{
					break;
				}
			}
		}
	}
	else
	{
		for (int i = allWidgets.size() - 1; i >= 0; i--)
		{
			if (allWidgets[i]->MouseCollision(mx, my))
			{
				if (allWidgets[i]->OnMouseButtonUp(_type))
				{
					break;
				}
			}
		}
	}
}

void UMGManager::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	int mx = LOWORD(lParam);
	int my = HIWORD(lParam);
	switch (message)
	{
	case WM_MOUSEMOVE:

		break;
	case WM_LBUTTONDOWN:
	{
		ProcessMouseEvent(MouseType::LButtonType,mx,my,true);
	}
		break;
	case WM_RBUTTONDOWN:
	{
		ProcessMouseEvent(MouseType::RButtonType, mx, my,true);
	}
		break;
	case WM_LBUTTONUP:
	{
		ProcessMouseEvent(MouseType::LButtonType, mx, my, false);
	}
		break;
	case WM_RBUTTONUP:
	{
		ProcessMouseEvent(MouseType::LButtonType, mx, my, false);
	}
		break;
	}
}

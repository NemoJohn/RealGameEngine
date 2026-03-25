#pragma once
#include "TSingleton.h"
#include "../utility.hpp"
#include "../UMG/UWidget.h"
class UMGManager :
    public TSingleton<UMGManager>
{
public:
    void AddWidget(UWidget* w);

    void OnRender();
    void SortZOrder();
    void ProcessMouseEvent(MouseType _type,int mx,int my,bool isPressed);

    void ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);
private:
    vector<UWidget*> allWidgets;
};


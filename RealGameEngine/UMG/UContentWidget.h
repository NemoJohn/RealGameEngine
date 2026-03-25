#pragma once
#include "UWidget.h"
class UContentWidget :
    public UWidget
{
public:
    void AddChild(UWidget* _child);

protected:

    UWidget* uniqueChild = nullptr;
private:

};


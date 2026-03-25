#pragma once
#include "UMG/UButton.h"
class TestButton2 :
    public UButton
{
public:
    bool OnMouseButtonDown(MouseType _type);
    virtual bool OnMouseButtonUp(MouseType _type);
};


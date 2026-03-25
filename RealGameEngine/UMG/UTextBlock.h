#pragma once
#include "UWidget.h"


class UTextBlock :
    public UWidget
{
public:
    UTextBlock();
    void Init(float FontWidth,float FontHeight);
    virtual void Render();

protected:
    LPD3DXFONT font;

    //×ÖÌå¿ò¿í¸ß
    float FontFrameWidth = 0;
    float FontFrameHeight = 0;
    RECT FrameRect;
private:
};


#pragma once
#include "UContentWidget.h"
class UButton :
    public UContentWidget
{
public:


	virtual void Init();
	virtual void Render();

	

protected:
    LPD3DXSPRITE spr = nullptr;

private:

};


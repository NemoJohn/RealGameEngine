#pragma once
#include "UWidget.h"
class UFrameAnimate :
    public UWidget
{
public:
	void CreateFrameAnimate(string _id, float w, float h, int _nFrames, float _fps);

	virtual void Init();
	virtual void Tick(float dt);
	virtual void Render();

protected:
	LPD3DXSPRITE spr = nullptr;

	float CellWidth = 0;
	float CellHeight = 0;
	int nFrames = 0;
	string TextureID = "";
	int curFrame = 0;

	//8~12FPS
	float fps = 0;

	float ct = 0;

private:


};


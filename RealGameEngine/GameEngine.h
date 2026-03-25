#pragma once

#include <windows.h>
#include <d3dx9.h>
#include <vector>
using namespace std;

#include "resource.h"

struct GameTime
{
	int hour = 0;
	int min = 0;
	int sec = 0;
};

class GameEngine
{
public:
	//注册窗口
	void RegisterWindows();
	//创建窗口
	void CreateWindows();
	//创建设备
	void CreateDevice();
	//逻辑更新
	void OnUpdate(float dt);
	//绘制
	void OnRender();
	//运行引擎
	void RunEngine();

	static LPDIRECT3DDEVICE9 GetDevice()
	{
		return m_pd3dDevice;
	}
	static float GetDeltaTime()
	{
		return deltaTime;
	}
	static int GetFPS()
	{
		return 1.0f / deltaTime;
	}
	static int GetPlaySecond()
	{
		return (int)playTime;
	}
	static GameTime GetPlayTime();
private:
	LPDIRECT3D9                    m_pD3D = nullptr;
	static LPDIRECT3DDEVICE9       m_pd3dDevice;
	HWND					       hWnd = nullptr;

	static float deltaTime;
	static float playTime;
	static GameTime gameTime;
};


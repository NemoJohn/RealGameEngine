#pragma once
#include "utility.hpp"

class UObject
{
public:
	UObject();
	virtual ~UObject();
	virtual void Init();
	virtual void BeginPlay();
	virtual void Tick(float dt);
	virtual void Update();
	virtual void Render();
	virtual void EndPlay();
	string GetName()const
	{
		return name;
	}
	string name;
protected:

	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
	
private:

};



#pragma once

#include "SubSystem/TSingleton.h"
#include "utility.hpp"

class WorldContext:public TSingleton<WorldContext>
{
public:
	void AddNode(class AActor* _actor);
	void OpenLevel(string LevelName);
	void SaveLevel(string LevelName);

	virtual void BeginPlay();
	virtual void Tick(float dt);
	virtual void Render();
private:
	vector<class AActor*> allActors;

};


#include "LightManager.h"
#include "../GameEngine.h"

void LightManager::AddLight(ULightComponent* lightRef)
{
	lightRef->LightID = allLights.size();
	GameEngine::GetDevice()->SetLight(lightRef->LightID,&lightRef->light);
	GameEngine::GetDevice()->LightEnable(lightRef->LightID, true);
	allLights.push_back(lightRef);
}

void LightManager::RemoveLight(int LightID)
{
	for (int i = 0; i < allLights.size(); i++)
	{
		GameEngine::GetDevice()->SetLight(allLights[i]->LightID, nullptr);
		GameEngine::GetDevice()->LightEnable(allLights[i]->LightID, false);
	}
	for (int i = 0; i < allLights.size(); i++)
	{
		if (allLights[i]->LightID == LightID)
		{
			auto p = allLights.begin() + i;
			allLights.erase(p);
		}
	}
	for (int i = 0; i < allLights.size(); i++)
	{
		allLights[i]->LightID = i;
		GameEngine::GetDevice()->SetLight(allLights[i]->LightID, &allLights[i]->light);
		GameEngine::GetDevice()->LightEnable(allLights[i]->LightID, true);
	}
}

void LightManager::Update()
{
	for (int i = 0; i < allLights.size(); i++)
	{
		GameEngine::GetDevice()->SetLight(allLights[i]->LightID, &allLights[i]->light);
		GameEngine::GetDevice()->LightEnable(allLights[i]->LightID, true);
	}
}

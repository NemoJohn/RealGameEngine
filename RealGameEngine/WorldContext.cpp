#include "WorldContext.h"
#include "AActor.h"
#include "xml/tinyxml.h"
#include "Component/UStaticMeshComponent.h"
#include "Component/UPointLightComponent.h"
#include "SubSystem/StaticMeshCache.h"
#include "Component/UCameraComponent.h"

void WorldContext::AddNode(AActor* _actor)
{
	allActors.push_back(_actor);
}

void WorldContext::OpenLevel(string LevelName)
{
	TiXmlDocument doc(LevelName.c_str());

	if (!doc.LoadFile())
	{
		MessageBox(nullptr, L"¾¯¸æ", L"¹Ø¿¨¼ÓÔØÊ§°Ü", MB_OK);
	}
	TiXmlElement* root = doc.FirstChildElement("World");
	TiXmlElement* Child = root->FirstChildElement("Actor");
	for (; Child != nullptr; Child = Child->NextSiblingElement("Actor"))
	{
		AActor* actor = new  AActor;
		TiXmlElement* compNode = Child->FirstChildElement("Component");
		for (; compNode != nullptr; compNode = compNode->NextSiblingElement("Component"))
		{
			string type = compNode->Attribute("type");
			float x = atof(compNode->Attribute("x"));
			float y = atof(compNode->Attribute("y"));
			float z = atof(compNode->Attribute("z"));
			if (type == "mesh")
			{
				UStaticMeshComponent* m = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
				//UStaticMeshComponent* m = new UStaticMeshComponent;
				m->name = "mesh";
				m->SetMeshAsset(StaticMeshCache::GetInstance()->FindStaticMeshAssetByID(compNode->Attribute("id")));
				m->SetupAttachment(actor);
				m->SetRelativeLocation(x, y, z);
			}
			else if (type == "pointLight")
			{
				float ar = atof(compNode->Attribute("ar"));
				float ag = atof(compNode->Attribute("ag"));
				float ab = atof(compNode->Attribute("ab"));
				float dr = atof(compNode->Attribute("dr"));
				float dg = atof(compNode->Attribute("dg"));
				float db = atof(compNode->Attribute("db"));
				float range = atof(compNode->Attribute("range"));
				float falloff = atof(compNode->Attribute("falloff"));
				UPointLightComponent* light = CreateDefaultSubobject<UPointLightComponent>("pointLight");
				light->SetupAttachment(actor);
				light->SetLightLocation(x, y, z);
				light->SetAmbientColor(ar, ag, ab);
				light->SetDiffuseColor(dr, dg, db);
				light->SetLightRange(range);
				light->SetLightFallOff(falloff);
			}
			else if (type == "camera")
			{
				UCameraComponent* camera1 = CreateDefaultSubobject<UCameraComponent>("camera");
				camera1->SetupAttachment(actor);
				camera1->SetCameraPosition(D3DXVECTOR3(x, y, z));
				bool active = atoi(compNode->Attribute("active"));
				if (active)
				{
					camera1->SetCameraActive(true);
				}
				
			}
		}
	}
}

void WorldContext::SaveLevel(string LevelName)
{
	TiXmlDocument doc;
	TiXmlElement* root = new TiXmlElement("World");
	doc.LinkEndChild(root);
	for (int i = 0; i < allActors.size(); i++)
	{
		TiXmlElement* actorNode = new TiXmlElement("Actor");
		actorNode->SetAttribute("x", allActors[i]->GetActorLocation().x);
		actorNode->SetAttribute("y", allActors[i]->GetActorLocation().y);
		actorNode->SetAttribute("z", allActors[i]->GetActorLocation().z);
		actorNode->SetAttribute("roll", allActors[i]->GetActorRotation().roll);
		actorNode->SetAttribute("pitch", allActors[i]->GetActorRotation().pitch);
		actorNode->SetAttribute("yaw", allActors[i]->GetActorRotation().yaw);
		actorNode->SetAttribute("sx", allActors[i]->GetActorScaling().x);
		actorNode->SetAttribute("sy", allActors[i]->GetActorScaling().y);
		actorNode->SetAttribute("sz", allActors[i]->GetActorScaling().z);
		for (int j = 0; j < allActors[i]->allSceneComponents.size(); j++)
		{
			TiXmlElement* compNode = new TiXmlElement("Component");
			string type = allActors[i]->allSceneComponents[j]->name;
			if (type == "mesh")
			{
				compNode->SetAttribute("type","mesh");
				compNode->SetAttribute("id", dynamic_cast<UStaticMeshComponent*>(allActors[i]->allSceneComponents[j])->meshID.c_str());
				compNode->SetAttribute("x", dynamic_cast<UStaticMeshComponent*>(allActors[i]->allSceneComponents[j])->GetWorldLocation().x);
				compNode->SetAttribute("y", dynamic_cast<UStaticMeshComponent*>(allActors[i]->allSceneComponents[j])->GetWorldLocation().y);
				compNode->SetAttribute("z", dynamic_cast<UStaticMeshComponent*>(allActors[i]->allSceneComponents[j])->GetWorldLocation().z);
			}
			else if (type == "pointLight")
			{
				compNode->SetAttribute("type", "pointLight");
				compNode->SetAttribute("x", dynamic_cast<UPointLightComponent*>(allActors[i]->allSceneComponents[j])->GetLightLocation().x);
				compNode->SetAttribute("y", dynamic_cast<UPointLightComponent*>(allActors[i]->allSceneComponents[j])->GetLightLocation().y);
				compNode->SetAttribute("z", dynamic_cast<UPointLightComponent*>(allActors[i]->allSceneComponents[j])->GetLightLocation().z);
				compNode->SetAttribute("ar", dynamic_cast<UPointLightComponent*>(allActors[i]->allSceneComponents[j])->GetAmbientColor().r);
				compNode->SetAttribute("ag", dynamic_cast<UPointLightComponent*>(allActors[i]->allSceneComponents[j])->GetAmbientColor().g);
				compNode->SetAttribute("ab", dynamic_cast<UPointLightComponent*>(allActors[i]->allSceneComponents[j])->GetAmbientColor().b);
				compNode->SetAttribute("dr", dynamic_cast<UPointLightComponent*>(allActors[i]->allSceneComponents[j])->GetDiffuseColor().r);
				compNode->SetAttribute("dg", dynamic_cast<UPointLightComponent*>(allActors[i]->allSceneComponents[j])->GetDiffuseColor().g);
				compNode->SetAttribute("db", dynamic_cast<UPointLightComponent*>(allActors[i]->allSceneComponents[j])->GetDiffuseColor().b);
				compNode->SetAttribute("range", dynamic_cast<UPointLightComponent*>(allActors[i]->allSceneComponents[j])->GetLightRange());
				compNode->SetAttribute("falloff", dynamic_cast<UPointLightComponent*>(allActors[i]->allSceneComponents[j])->GetLightFallOff());
			}
			else if (type == "camera")
			{
				compNode->SetAttribute("type", "camera");
				compNode->SetAttribute("x", dynamic_cast<UCameraComponent*>(allActors[i]->allSceneComponents[j])->GetCameraPosition().x);
				compNode->SetAttribute("y", dynamic_cast<UCameraComponent*>(allActors[i]->allSceneComponents[j])->GetCameraPosition().y);
				compNode->SetAttribute("z", dynamic_cast<UCameraComponent*>(allActors[i]->allSceneComponents[j])->GetCameraPosition().z);
				bool active = dynamic_cast<UCameraComponent*>(allActors[i]->allSceneComponents[j])->GetCameraActive();
				if (active)
				{
					compNode->SetAttribute("active", "1");
				}
				else
				{
					compNode->SetAttribute("active", "0");
				}
			}
			actorNode->LinkEndChild(compNode);
		}
		root->LinkEndChild(actorNode);
	}
	doc.SaveFile(LevelName.c_str());
}

void WorldContext::BeginPlay()
{
	for (int i = 0; i < allActors.size(); i++)
	{
		allActors[i]->BeginPlay();
	}
}

void WorldContext::Tick(float dt)
{
	for (int i = 0; i < allActors.size(); i++)
	{
		allActors[i]->Tick(dt);
	}
}

void WorldContext::Render()
{
	for (int i = 0; i < allActors.size(); i++)
	{
		allActors[i]->Render();
	}
}

#include "MyActor_1.h"
#include "Component/UStaticMeshComponent.h"
#include "Component/UPointLightComponent.h"
#include "SubSystem/StaticMeshCache.h"
#include "Component/UCameraComponent.h"

MyActor_1::MyActor_1()
{
    comp = CreateDefaultSubobject<UStaticMeshComponent>("MyComp");
    comp->SetMeshAsset(StaticMeshCache::GetInstance()->FindStaticMeshAssetByID("1001"));
    comp->SetupAttachment(this);
    comp->SetRelativeLocation(0, 0, 0);

    light = CreateDefaultSubobject<UPointLightComponent>("MyLight");
    light->SetupAttachment(this);
    light->SetLightLocation(0, 0, -2);
    light->SetAmbientColor(0.3f, 0.3f, 0.3f);
    light->SetDiffuseColor(0.7f, 0.7f, 0.7f);
    light->SetLightRange(100);
    light->SetLightFallOff(1.2f);

    camera1 = CreateDefaultSubobject<UCameraComponent>("MyCamera");
    camera1->SetCameraPosition(D3DXVECTOR3(0, 0, 0));
    camera1->SetCameraActive(true);

    
}

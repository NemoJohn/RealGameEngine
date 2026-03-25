#include "MyActor_2.h"
#include "Component/UStaticMeshComponent.h"
#include "Component/UPointLightComponent.h"
#include "SubSystem/StaticMeshCache.h"
#include "Component/UCameraComponent.h"
MyActor_2::MyActor_2()
{
    comp1 = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
    comp1->SetMeshAsset(StaticMeshCache::GetInstance()->FindStaticMeshAssetByID("1001"));
    comp1->SetupAttachment(this);
    comp1->SetRelativeLocation(0, 0, 0);

}

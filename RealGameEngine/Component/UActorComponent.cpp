#include "UActorComponent.h"
#include "../AActor.h"

void UActorComponent::SetupAttachment(UObject* _parent)
{
	parent = _parent;
	AActor* p = dynamic_cast<AActor*>(parent);
	p->AddActorComponent(this);
}

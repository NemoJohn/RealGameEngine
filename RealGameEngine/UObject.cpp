#include "UObject.h"
#include "GameEngine.h"

UObject::UObject()
{
	m_pDevice = GameEngine::GetDevice();
}

UObject::~UObject()
{
	EndPlay();
}

void UObject::Init()
{
}

void UObject::BeginPlay()
{
}

void UObject::Tick(float dt)
{
}

void UObject::Update()
{
}

void UObject::Render()
{
}

void UObject::EndPlay()
{
}

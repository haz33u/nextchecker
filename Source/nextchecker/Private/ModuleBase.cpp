#include "ModuleBase.h"

AModuleBase::AModuleBase()
{
    PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;
}

void AModuleBase::BeginPlay()
{
    Super::BeginPlay();
}

void AModuleBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

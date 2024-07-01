#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UInventoryComponent::AddBaseModule(const FBaseModule& NewModule)
{
    BaseModules.Add(NewModule);
}

void UInventoryComponent::AddWeaponModule(const FWeaponModule& NewModule)
{
    WeaponModules.Add(NewModule);
}

void UInventoryComponent::AddCamModule(const FCamModule& NewModule)
{
    CamModules.Add(NewModule);
}

FBaseModule UInventoryComponent::GetBaseModule(int32 Index)
{
    return BaseModules.IsValidIndex(Index) ? BaseModules[Index] : FBaseModule();
}

FWeaponModule UInventoryComponent::GetWeaponModule(int32 Index)
{
    return WeaponModules.IsValidIndex(Index) ? WeaponModules[Index] : FWeaponModule();
}

FCamModule UInventoryComponent::GetCamModule(int32 Index)
{
    return CamModules.IsValidIndex(Index) ? CamModules[Index] : FCamModule();
}

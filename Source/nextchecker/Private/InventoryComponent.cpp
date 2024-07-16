#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UInventoryComponent::AddItem(const FInventoryItemStruct& NewItem)
{
    Items.Add(NewItem);
}

const TArray<FInventoryItemStruct>& UInventoryComponent::GetItems() const
{
    return Items;
}

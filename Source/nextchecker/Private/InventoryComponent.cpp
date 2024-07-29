#include "InventoryComponent.h"
#include "InventoryItemStruct.h" // Убедитесь, что этот include добавлен

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

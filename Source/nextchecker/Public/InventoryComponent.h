﻿#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryItemStruct.h"
#include "InventoryComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NEXTCHECKER_API UInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UInventoryComponent();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable, Category = "Inventory")
        void AddItem(const FInventoryItemStruct& NewItem);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
        const TArray<FInventoryItemStruct>& GetItems() const;

private:
    UPROPERTY()
        TArray<FInventoryItemStruct> Items;
};

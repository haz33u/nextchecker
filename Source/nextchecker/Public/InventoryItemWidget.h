#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemStruct.h"
#include "InventoryItemWidget.generated.h"

UCLASS()
class NEXTCHECKER_API UInventoryItemWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
        class UTextBlock* ItemNameText;

    UPROPERTY(meta = (BindWidget))
        class UImage* ItemIconImage;

    UFUNCTION(BlueprintCallable)
        void Setup(const FInventoryItemStruct& ItemData);
};

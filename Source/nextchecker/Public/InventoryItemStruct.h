#pragma once
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/Texture2D.h"
#include "InventoryItemStruct.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItemStruct
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
        FString ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
        UTexture2D* ItemIcon;

    FInventoryItemStruct()
        : ItemName("Default")
        , ItemIcon(nullptr)
    {
    }
};

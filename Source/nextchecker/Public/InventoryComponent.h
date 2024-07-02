#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ModuleBase.h"
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
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
        TArray<FBaseModule> BaseModules;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
        TArray<FWeaponModule> WeaponModules;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
        TArray<FCamModule> CamModules;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
        void AddBaseModule(const FBaseModule& NewModule);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
        void AddWeaponModule(const FWeaponModule& NewModule);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
        void AddCamModule(const FCamModule& NewModule);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
        FBaseModule GetBaseModule(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
        FWeaponModule GetWeaponModule(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
        FCamModule GetCamModule(int32 Index);
};

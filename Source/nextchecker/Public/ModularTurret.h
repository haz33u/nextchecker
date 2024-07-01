#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ModuleBase.h"
#include "InventoryComponent.h"
#include "ModularTurret.generated.h"

UCLASS()
class NEXTCHECKER_API AModularTurret : public APawn
{
    GENERATED_BODY()

public:
    AModularTurret();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
        FBaseModule BaseModule;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
        FWeaponModule WeaponModule;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cam")
        FCamModule CamModule;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UStaticMeshComponent* BaseMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UStaticMeshComponent* GunMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UStaticMeshComponent* TopMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UInventoryComponent* InventoryComponent;

    void SetBaseModule(const FBaseModule& NewModule);
    void SetWeaponModule(const FWeaponModule& NewModule);
    void SetCamModule(const FCamModule& NewModule);

    void ConfigureTurret();

    UFUNCTION(BlueprintCallable, Category = "Turret")
        void Fire();

private:
    void ApplyBaseModule();
    void ApplyWeaponModule();
    void ApplyCamModule();

    FTimerHandle FireRateHandle;
};

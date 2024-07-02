#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ModuleBase.h"
#include "Projectile.h"
#include "ModularTurret.generated.h"

UCLASS()
class NEXTCHECKER_API AModularTurret : public AActor
{
    GENERATED_BODY()

public:
    AModularTurret();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UStaticMeshComponent* BaseMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UStaticMeshComponent* GunMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UStaticMeshComponent* TopMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UStaticMeshComponent* BarrelMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        class UInventoryComponent* InventoryComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
        TSubclassOf<AProjectile> ProjectileClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
        float FireRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
        float DetectionRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
        float FiringRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
        float RotationSpeed;

private:
    void ApplyBaseModule();
    void ApplyWeaponModule();
    void ApplyCamModule();
    void ConfigureTurret();
    void Fire();
    AActor* FindTarget();

    FTimerHandle FireRateHandle;
    FBaseModule BaseModule;
    FWeaponModule WeaponModule;
    FCamModule CamModule;
};

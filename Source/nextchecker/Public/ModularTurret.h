#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ModularTurret.generated.h"

class AProjectile;

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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
        float RotationSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
        TSubclassOf<AProjectile> ProjectileType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
        float FireRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
        float DetectionRange;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UStaticMeshComponent* BaseMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UStaticMeshComponent* GunMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UStaticMeshComponent* TopMesh;

    void UpdateTurretComponents(UStaticMeshComponent* NewBase, UStaticMeshComponent* NewGun, UStaticMeshComponent* NewTop, float NewFireRate, float NewRotationSpeed);

private:
    FTimerHandle FireRateTimerHandle;
    APawn* TargetPawn;

    void Fire();
    void FindTarget();
    void RotateTowardsTarget();
};

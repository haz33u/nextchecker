#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ModularTurret2.generated.h"

class AProjectile;
class UCapsuleComponent;
class UFloatingPawnMovement;

UCLASS()
class NEXTCHECKER_API AModularTurret2 : public APawn
{
    GENERATED_BODY()

public:
    AModularTurret2();

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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UCapsuleComponent* CapsuleComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UFloatingPawnMovement* MovementComponent;

    void UpdateTurretComponents(UStaticMeshComponent* NewBase, UStaticMeshComponent* NewGun, UStaticMeshComponent* NewTop, float NewFireRate, float NewRotationSpeed);

private:
    FTimerHandle FireRateTimerHandle;
    APawn* TargetPawn;

    void Fire();
    void FindTarget();
    void RotateTowardsTarget();
};

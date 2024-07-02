#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseTurret.generated.h"

UCLASS()
class NEXTCHECKER_API ABaseTurret : public APawn
{
    GENERATED_BODY()

public:
    ABaseTurret();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        class UStaticMeshComponent* BaseMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        class UStaticMeshComponent* GunMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        class UStaticMeshComponent* TopMesh;

    UPROPERTY(EditAnywhere, Category = "Turret")
        float Health;

    UPROPERTY(EditAnywhere, Category = "Turret")
        float Damage;

    UPROPERTY(EditAnywhere, Category = "Turret")
        float FireRate;

    UPROPERTY(EditAnywhere, Category = "Turret")
        float DetectionRange;

    UPROPERTY(EditAnywhere, Category = "Turret")
        float RotationSpeed;

    UPROPERTY(EditAnywhere, Category = "Turret")
        FVector MuzzleOffset;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Turret")
        TSubclassOf<class ANewBullet> BulletClass;

    FTimerHandle FireRateTimerHandle;

    AActor* ClosestEnemy;

protected:
    void Fire();
    void FindTarget();
    void RotateTowardsTarget();
    bool IsEnemyInRange(AActor* Enemy);

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    void SetupTurretParameters();
};

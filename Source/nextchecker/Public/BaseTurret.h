#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTurret.generated.h"

UCLASS()
class NEXTCHECKER_API ABaseTurret : public AActor
{
    GENERATED_BODY()

public:
    ABaseTurret();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UStaticMeshComponent* BaseMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UStaticMeshComponent* TurretMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UStaticMeshComponent* GunMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        USceneComponent* MuzzleLocation;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
        TSubclassOf<class AProjectile> ProjectileClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
        float FireRate;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
        float FireRange;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
        float RotationSpeed;

    FTimerHandle FireRateTimerHandle;
    APawn* TargetPawn;

    void CheckFireCondition();
    bool InFireRange();
    void RotateTurret(FVector LookAtTarget);
    void Fire();
};

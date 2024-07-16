#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class NEXTCHECKER_API AProjectile : public AActor
{
    GENERATED_BODY()

public:
    AProjectile();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UStaticMeshComponent* ProjectileMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
        class UProjectileMovementComponent* ProjectileMovement;

    void FireInDirection(const FVector& ShootDirection);
};

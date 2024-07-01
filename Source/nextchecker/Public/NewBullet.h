#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NewBullet.generated.h" // Этот include должен быть последним

UCLASS()
class NEXTCHECKER_API ANewBullet : public AActor
{
    GENERATED_BODY()

public:
    ANewBullet();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UStaticMeshComponent* BulletMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        class UProjectileMovementComponent* ProjectileMovement;

    void FireInDirection(const FVector& ShootDirection);
};

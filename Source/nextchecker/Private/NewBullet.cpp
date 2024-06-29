#include "NewBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"

ANewBullet::ANewBullet()
{
    PrimaryActorTick.bCanEverTick = true;

    BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
    RootComponent = BulletMesh;

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->SetUpdatedComponent(BulletMesh);
    ProjectileMovement->InitialSpeed = 3000.f;
    ProjectileMovement->MaxSpeed = 3000.f;
}

void ANewBullet::BeginPlay()
{
    Super::BeginPlay();
}

void ANewBullet::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ANewBullet::FireInDirection(const FVector& ShootDirection)
{
    if (ProjectileMovement)
    {
        ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
    }
}

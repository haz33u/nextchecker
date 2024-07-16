#include "BaseTurret.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Projectile.h"

ABaseTurret::ABaseTurret()
{
    PrimaryActorTick.bCanEverTick = true;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
    RootComponent = BaseMesh;

    TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
    TurretMesh->SetupAttachment(BaseMesh);

    GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
    GunMesh->SetupAttachment(TurretMesh);

    MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
    MuzzleLocation->SetupAttachment(GunMesh);

    FireRate = 2.0f;
    FireRange = 1000.0f;
    RotationSpeed = 10.0f;
}

void ABaseTurret::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ABaseTurret::CheckFireCondition, FireRate, true);
}

void ABaseTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (TargetPawn && InFireRange())
    {
        RotateTurret(TargetPawn->GetActorLocation());
    }
}

void ABaseTurret::CheckFireCondition()
{
    if (TargetPawn && InFireRange())
    {
        Fire();
    }
    else
    {
        TArray<AActor*> EnemyPawns;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawn::StaticClass(), EnemyPawns);

        float ClosestDistance = FireRange;
        APawn* ClosestPawn = nullptr;

        for (AActor* Enemy : EnemyPawns)
        {
            float DistanceToEnemy = FVector::Dist(GetActorLocation(), Enemy->GetActorLocation());
            if (DistanceToEnemy < ClosestDistance)
            {
                ClosestDistance = DistanceToEnemy;
                ClosestPawn = Cast<APawn>(Enemy);
            }
        }

        TargetPawn = ClosestPawn;
    }
}

bool ABaseTurret::InFireRange()
{
    if (TargetPawn)
    {
        float DistanceToTarget = FVector::Dist(GetActorLocation(), TargetPawn->GetActorLocation());
        return DistanceToTarget <= FireRange;
    }
    return false;
}

void ABaseTurret::RotateTurret(FVector LookAtTarget)
{
    FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
    FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
    FRotator CurrentRotation = TurretMesh->GetComponentRotation();

    TurretMesh->SetWorldRotation(FMath::RInterpTo(CurrentRotation, LookAtRotation, GetWorld()->GetDeltaSeconds(), RotationSpeed));
}

void ABaseTurret::Fire()
{
    if (ProjectileClass)
    {
        FVector SpawnLocation = MuzzleLocation->GetComponentLocation();
        FRotator SpawnRotation = MuzzleLocation->GetComponentRotation();
        AProjectile* TempProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);

        TempProjectile->SetOwner(this);
    }
}

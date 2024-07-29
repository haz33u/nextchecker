#include "ModularTurret2.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

AModularTurret2::AModularTurret2()
{
    PrimaryActorTick.bCanEverTick = true;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    RootComponent = CapsuleComponent;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
    BaseMesh->SetupAttachment(CapsuleComponent);

    GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
    GunMesh->SetupAttachment(BaseMesh);

    TopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopMesh"));
    TopMesh->SetupAttachment(GunMesh);

    MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));

    RotationSpeed = 90.0f;
    FireRate = 1.0f;
    DetectionRange = 1000.0f;
}

void AModularTurret2::BeginPlay()
{
    Super::BeginPlay();
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &AModularTurret2::Fire, FireRate, true);
}

void AModularTurret2::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FindTarget();
    RotateTowardsTarget();
}

void AModularTurret2::UpdateTurretComponents(UStaticMeshComponent* NewBase, UStaticMeshComponent* NewGun, UStaticMeshComponent* NewTop, float NewFireRate, float NewRotationSpeed)
{
    BaseMesh = NewBase;
    GunMesh = NewGun;
    TopMesh = NewTop;
    FireRate = NewFireRate;
    RotationSpeed = NewRotationSpeed;
}

void AModularTurret2::Fire()
{
    if (ProjectileType && TargetPawn)
    {
        FVector MuzzleLocation = GunMesh->GetSocketLocation("Muzzle");
        FRotator MuzzleRotation = GunMesh->GetSocketRotation("Muzzle");

        UWorld* World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;

            AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileType, MuzzleLocation, MuzzleRotation, SpawnParams);
            if (Projectile)
            {
                FVector LaunchDirection = MuzzleRotation.Vector();
                Projectile->FireInDirection(LaunchDirection);
            }
        }
    }
}

void AModularTurret2::FindTarget()
{
    FVector TurretLocation = GetActorLocation();
    TArray<AActor*> PotentialTargets;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawn::StaticClass(), PotentialTargets);

    float ClosestDistance = DetectionRange;
    TargetPawn = nullptr;

    for (AActor* Actor : PotentialTargets)
    {
        APawn* Pawn = Cast<APawn>(Actor);
        if (Pawn && Pawn != this && Pawn->IsPlayerControlled())
        {
            float Distance = FVector::Dist(TurretLocation, Pawn->GetActorLocation());
            if (Distance < ClosestDistance)
            {
                ClosestDistance = Distance;
                TargetPawn = Pawn;
            }
        }
    }
}

void AModularTurret2::RotateTowardsTarget()
{
    if (TargetPawn)
    {
        FVector Direction = (TargetPawn->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        FRotator DesiredRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
        FRotator CurrentRotation = GetActorRotation();
        FRotator NewRotation = FMath::RInterpTo(CurrentRotation, DesiredRotation, GetWorld()->GetDeltaSeconds(), RotationSpeed);
        SetActorRotation(NewRotation);
    }
}
    
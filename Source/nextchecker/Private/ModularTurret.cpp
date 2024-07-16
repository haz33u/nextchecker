#include "ModularTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"

AModularTurret::AModularTurret()
{
    PrimaryActorTick.bCanEverTick = true;
    RotationSpeed = 5.0f;
    FireRate = 1.0f;
    DetectionRange = 1000.0f;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
    RootComponent = BaseMesh;

    GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
    GunMesh->SetupAttachment(BaseMesh);

    TopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopMesh"));
    TopMesh->SetupAttachment(GunMesh);
}

void AModularTurret::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AModularTurret::Fire, FireRate, true);
}

void AModularTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FindTarget();
    RotateTowardsTarget();
}

void AModularTurret::Fire()
{
    if (TargetPawn && ProjectileType)
    {
        FVector MuzzleLocation = GunMesh->GetSocketLocation(FName("Muzzle"));
        FRotator MuzzleRotation = GunMesh->GetSocketRotation(FName("Muzzle"));

        AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileType, MuzzleLocation, MuzzleRotation);
        if (Projectile)
        {
            FVector LaunchDirection = (TargetPawn->GetActorLocation() - MuzzleLocation).GetSafeNormal();
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Launching projectile in direction: %s"), *LaunchDirection.ToString()));
            Projectile->FireInDirection(LaunchDirection);
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to spawn projectile"));
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("No target or projectile type specified"));
    }
}

void AModularTurret::FindTarget()
{
    APawn* NearestPawn = nullptr;
    float MinDistance = DetectionRange;

    for (TActorIterator<APawn> It(GetWorld()); It; ++It)
    {
        APawn* Pawn = *It;
        if (Pawn && Pawn->ActorHasTag(FName("Enemy")))
        {
            float Distance = FVector::Dist(Pawn->GetActorLocation(), GetActorLocation());
            if (Distance < MinDistance)
            {
                MinDistance = Distance;
                NearestPawn = Pawn;
            }
        }
    }
    TargetPawn = NearestPawn;
}

void AModularTurret::RotateTowardsTarget()
{
    if (TargetPawn)
    {
        FVector Direction = (TargetPawn->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        FRotator LookAtRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
        FRotator CurrentRotation = GunMesh->GetComponentRotation();
        FRotator NewRotation = FMath::RInterpTo(CurrentRotation, LookAtRotation, GetWorld()->GetDeltaSeconds(), RotationSpeed);
        GunMesh->SetWorldRotation(NewRotation);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Rotating towards target: %s"), *Direction.ToString()));
    }
}

void AModularTurret::UpdateTurretComponents(UStaticMeshComponent* NewBase, UStaticMeshComponent* NewGun, UStaticMeshComponent* NewTop, float NewFireRate, float NewRotationSpeed)
{
    if (NewBase)
    {
        BaseMesh = NewBase;
    }
    if (NewGun)
    {
        GunMesh = NewGun;
    }
    if (NewTop)
    {
        TopMesh = NewTop;
    }
    FireRate = NewFireRate;
    RotationSpeed = NewRotationSpeed;
}

#include "ModularTurret.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "InventoryComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AModularTurret::AModularTurret()
{
    PrimaryActorTick.bCanEverTick = true;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
    RootComponent = BaseMesh;

    GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
    GunMesh->SetupAttachment(BaseMesh);

    TopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopMesh"));
    TopMesh->SetupAttachment(GunMesh);

    BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMesh"));
    BarrelMesh->SetupAttachment(GunMesh);

    InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void AModularTurret::BeginPlay()
{
    Super::BeginPlay();
    ConfigureTurret();
    GetWorldTimerManager().SetTimer(FireRateHandle, this, &AModularTurret::Fire, 1.0f / FireRate, true);
}

void AModularTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AActor* Target = FindTarget();
    if (Target)
    {
        FVector Direction = Target->GetActorLocation() - GetActorLocation();
        FRotator NewRotation = Direction.Rotation();
        NewRotation.Pitch = 0;
        NewRotation.Roll = 0;
        SetActorRotation(FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, RotationSpeed));
    }
}

AActor* AModularTurret::FindTarget()
{
    TArray<AActor*> OverlappingActors;
    TArray<AActor*> IgnoreActors;
    IgnoreActors.Add(this);

    UKismetSystemLibrary::SphereOverlapActors(this, GetActorLocation(), DetectionRange, TArray<TEnumAsByte<EObjectTypeQuery>>(), AActor::StaticClass(), IgnoreActors, OverlappingActors);

    AActor* ClosestTarget = nullptr;
    float ClosestDistance = DetectionRange;

    for (AActor* Actor : OverlappingActors)
    {
        float Distance = FVector::Dist(Actor->GetActorLocation(), GetActorLocation());
        if (Distance < ClosestDistance)
        {
            ClosestTarget = Actor;
            ClosestDistance = Distance;
        }
    }

    return ClosestTarget;
}

void AModularTurret::ApplyBaseModule()
{
    RotationSpeed = BaseModule.RotationSpeed;
}

void AModularTurret::ApplyWeaponModule()
{
    FireRate = WeaponModule.FireRate;
}

void AModularTurret::ApplyCamModule()
{
    DetectionRange = CamModule.DetectionRange;
    FiringRange = CamModule.FiringRange;
}

void AModularTurret::ConfigureTurret()
{
    if (InventoryComponent)
    {
        if (InventoryComponent->BaseModules.Num() > 0)
        {
            BaseModule = InventoryComponent->GetBaseModule(0);
            ApplyBaseModule();
        }
        if (InventoryComponent->WeaponModules.Num() > 0)
        {
            WeaponModule = InventoryComponent->GetWeaponModule(0);
            ApplyWeaponModule();
        }
        if (InventoryComponent->CamModules.Num() > 0)
        {
            CamModule = InventoryComponent->GetCamModule(0);
            ApplyCamModule();
        }
    }
}

void AModularTurret::Fire()
{
    FVector MuzzleLocation = BarrelMesh->GetSocketLocation(TEXT("Muzzle"));
    FRotator MuzzleRotation = BarrelMesh->GetSocketRotation(TEXT("Muzzle"));

    AActor* Target = FindTarget();

    if (Target)
    {
        FVector Direction = Target->GetActorLocation() - MuzzleLocation;
        Direction.Normalize();

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();

        AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

        if (Projectile)
        {
            Projectile->FireInDirection(Direction);
        }
    }
}

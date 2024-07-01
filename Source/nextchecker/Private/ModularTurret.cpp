#include "ModularTurret.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AModularTurret::AModularTurret()
{
    PrimaryActorTick.bCanEverTick = true;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
    RootComponent = BaseMesh;

    GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
    GunMesh->SetupAttachment(BaseMesh);

    TopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopMesh"));
    TopMesh->SetupAttachment(GunMesh);

    InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void AModularTurret::BeginPlay()
{
    Super::BeginPlay();
    ConfigureTurret();
    GetWorldTimerManager().SetTimer(FireRateHandle, this, &AModularTurret::Fire, 1.0f / WeaponModule.FireRate, true);
}

void AModularTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AModularTurret::SetBaseModule(const FBaseModule& NewModule)
{
    BaseModule = NewModule;
    ApplyBaseModule();
}

void AModularTurret::SetWeaponModule(const FWeaponModule& NewModule)
{
    WeaponModule = NewModule;
    ApplyWeaponModule();
}

void AModularTurret::SetCamModule(const FCamModule& NewModule)
{
    CamModule = NewModule;
    ApplyCamModule();
}

void AModularTurret::ApplyBaseModule()
{
    // Применяем параметры BaseModule к турели
    Health = BaseModule.Health;
    Damage = BaseModule.Damage;
    RotationSpeed = BaseModule.RotationSpeed;
}

void AModularTurret::ApplyWeaponModule()
{
    // Применяем параметры WeaponModule к турели
    FireRate = WeaponModule.FireRate;
    DamageType = WeaponModule.DamageType;
}

void AModularTurret::ApplyCamModule()
{
    // Применяем параметры CamModule к турели
    DetectionRange = CamModule.DetectionRange;
    FiringRange = CamModule.FiringRange;
    TargetType = CamModule.TargetType;
}

void AModularTurret::ConfigureTurret()
{
    if (InventoryComponent)
    {
        if (InventoryComponent->BaseModules.Num() > 0)
        {
            SetBaseModule(InventoryComponent->GetBaseModule(0));
        }
        if (InventoryComponent->WeaponModules.Num() > 0)
        {
            SetWeaponModule(InventoryComponent->GetWeaponModule(0));
        }
        if (InventoryComponent->CamModules.Num() > 0)
        {
            SetCamModule(InventoryComponent->GetCamModule(0));
        }
    }
}

void AModularTurret::Fire()
{
    // Логика стрельбы
    FVector MuzzleLocation = GunMesh->GetSocketLocation(TEXT("Muzzle"));
    FRotator MuzzleRotation = GunMesh->GetSocketRotation(TEXT("Muzzle"));

    AActor* Target = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0); // Текущий игрок как цель для тестирования

    if (Target)
    {
        FVector Direction = Target->GetActorLocation() - MuzzleLocation;
        Direction.Normalize();

        // Создание снаряда (Projectile)
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();

        AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(MuzzleLocation, Direction.Rotation(), SpawnParams);

        if (Projectile)
        {
            Projectile->FireInDirection(Direction);
        }
    }
}

#include "NewTurret.h"
#include "NewBullet.h"
#include "NewEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Конструктор
ANewTurret::ANewTurret()
{
    PrimaryActorTick.bCanEverTick = true;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
    RootComponent = BaseMesh;

    GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
    GunMesh->SetupAttachment(BaseMesh);

    TopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopMesh"));
    TopMesh->SetupAttachment(GunMesh);

    Health = 100.f;
    Damage = 20.f;
    FireRate = 1.f;
    DetectionRange = 1000.f;
    RotationSpeed = 10.f;
    MuzzleOffset = FVector(100.f, 0.f, 0.f);
    ClosestEnemy = nullptr;
}

// Начало игры
void ANewTurret::BeginPlay()
{
    Super::BeginPlay();
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &ANewTurret::FindTarget, FireRate, true);
}

// Обновление каждого кадра
void ANewTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    RotateTowardsTarget();
}

// Настройка компонентов ввода
void ANewTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    // Здесь можно добавить привязки действий и осей
}

// Огонь по цели
void ANewTurret::Fire()
{
    if (BulletClass && ClosestEnemy)
    {
        FVector MuzzleLocation = GunMesh->GetComponentLocation() + MuzzleOffset;
        FRotator MuzzleRotation = GunMesh->GetComponentRotation();
        UWorld* World = GetWorld();
        if (World)
        {
            ANewBullet* Bullet = World->SpawnActor<ANewBullet>(BulletClass, MuzzleLocation, MuzzleRotation);
            if (Bullet)
            {
                FVector LaunchDirection = MuzzleRotation.Vector();
                Bullet->FireInDirection(LaunchDirection);
            }
        }
    }
}

// Поиск цели
void ANewTurret::FindTarget()
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANewEnemy::StaticClass(), FoundActors);

    AActor* NearestEnemy = nullptr;
    float MinDistance = DetectionRange;

    for (AActor* Actor : FoundActors)
    {
        float Distance = FVector::Dist(Actor->GetActorLocation(), GetActorLocation());
        if (Distance < MinDistance)
        {
            MinDistance = Distance;
            NearestEnemy = Actor;
        }
    }

    if (IsEnemyInRange(NearestEnemy))
    {
        ClosestEnemy = NearestEnemy;
        Fire();
    }
}

// Вращение к цели
void ANewTurret::RotateTowardsTarget()
{
    if (ClosestEnemy)
    {
        FVector Direction = ClosestEnemy->GetActorLocation() - GetActorLocation();
        FRotator TargetRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
        FRotator SmoothRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), RotationSpeed);
        SetActorRotation(SmoothRotation);
    }
}

// Проверка, находится ли враг в пределах досягаемости
bool ANewTurret::IsEnemyInRange(AActor* Enemy)
{
    if (Enemy)
    {
        float Distance = FVector::Dist(Enemy->GetActorLocation(), GetActorLocation());
        return Distance <= DetectionRange;
    }
    return false;
}

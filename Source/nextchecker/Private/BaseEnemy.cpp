#include "BaseEnemy.h"

ABaseEnemy::ABaseEnemy()
{
    PrimaryActorTick.bCanEverTick = true;
    Health = 100.f;
}

void ABaseEnemy::BeginPlay()
{
    Super::BeginPlay();
}

void ABaseEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

float ABaseEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Health -= DamageAmount;
    if (Health <= 0.f)
    {
        Destroy();
    }
    return DamageAmount;
}

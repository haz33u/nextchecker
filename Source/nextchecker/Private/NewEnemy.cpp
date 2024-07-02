#include "NewEnemy.h"

// Конструктор
ANewEnemy::ANewEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    MaxHealth = 100.0f;
    CurrentHealth = MaxHealth;
}

// Начало игры
void ANewEnemy::BeginPlay()
{
    Super::BeginPlay();
}

// Обновление каждого кадра
void ANewEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Функция получения урона
float ANewEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    if (ActualDamage > 0.0f)
    {
        CurrentHealth -= ActualDamage;
        if (CurrentHealth <= 0.0f)
        {
            // Логика смерти
            Destroy();
        }
    }

    return ActualDamage;
}

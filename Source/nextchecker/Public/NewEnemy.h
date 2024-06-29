#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NewEnemy.generated.h"

UCLASS()
class NEXTCHECKER_API ANewEnemy : public ACharacter
{
    GENERATED_BODY()

public:
    // Конструктор
    ANewEnemy();

protected:
    // Начало игры
    virtual void BeginPlay() override;

public:
    // Обновление каждого кадра
    virtual void Tick(float DeltaTime) override;

    // Функция получения урона
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
    // Переменные для здоровья
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
        float MaxHealth;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
        float CurrentHealth;
};

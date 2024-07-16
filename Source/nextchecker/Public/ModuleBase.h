#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ModuleBase.generated.h"

UENUM(BlueprintType)
enum class ERarityLevel : uint8
{
    Common,
    Uncommon,
    Rare,
    Epic,
    Legendary,
    Magnificent,
    Excellent
};

USTRUCT(BlueprintType)
struct FBaseModule
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float RotationSpeed;

    FBaseModule(float InDamage = 0.0f, float InHealth = 0.0f, float InRotationSpeed = 0.0f)
        : Damage(InDamage), Health(InHealth), RotationSpeed(InRotationSpeed) {}
};

USTRUCT(BlueprintType)
struct FWeaponModule
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float FireRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString DamageType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        ERarityLevel Rarity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<FString> Effects;

    FWeaponModule(float InFireRate = 1.0f, FString InDamageType = "Physical", ERarityLevel InRarity = ERarityLevel::Common, TArray<FString> InEffects = {})
        : FireRate(InFireRate), DamageType(InDamageType), Rarity(InRarity), Effects(InEffects) {}
};

USTRUCT(BlueprintType)
struct FCamModule
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float DetectionRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float FiringRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString TargetType;

    FCamModule(float InDetectionRange = 1000.0f, float InFiringRange = 1000.0f, FString InTargetType = "Ground")
        : DetectionRange(InDetectionRange), FiringRange(InFiringRange), TargetType(InTargetType) {}
};

UCLASS()
class NEXTCHECKER_API AModuleBase : public AActor
{
    GENERATED_BODY()

public:
    AModuleBase();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        UStaticMeshComponent* MeshComponent;
};

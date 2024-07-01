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
    Excellent // "Excelent" фишка игры
};

USTRUCT(BlueprintType)
struct FBaseModule
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float Damage = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float Health = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float RotationSpeed = 0.0f;

    FBaseModule(float InDamage = 0.0f, float InHealth = 0.0f, float InRotationSpeed = 0.0f)
        : Damage(InDamage), Health(InHealth), RotationSpeed(InRotationSpeed) {}
};

USTRUCT(BlueprintType)
struct FWeaponModule
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float FireRate = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString DamageType = "Physical";

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        ERarityLevel Rarity = ERarityLevel::Common;

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
        float DetectionRange = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float FiringRange = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString TargetType = "Ground"; // Ground, Air, Both

    FCamModule(float InDetectionRange = 1000.0f, float InFiringRange = 1000.0f, FString InTargetType = "Ground")
        : DetectionRange(InDetectionRange), FiringRange(InFiringRange), TargetType(InTargetType) {}
};

UCLASS()
class NEXTCHECKER_API AModuleBase : public AActor
{
    GENERATED_BODY()

public:
    AModuleBase();
};

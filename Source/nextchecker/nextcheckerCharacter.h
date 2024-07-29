#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "nextcheckerCharacter.generated.h"

UCLASS(config = Game)
class AnextcheckerCharacter : public ACharacter
{
    GENERATED_BODY()

        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
        class USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
        class UCameraComponent* FollowCamera;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        class UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        class UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        class UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        class UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        class UInputAction* OpenInventoryAction;

public:
    AnextcheckerCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void OpenInventory();

public:
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

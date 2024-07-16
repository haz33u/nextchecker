#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyPlayerController.h"  // Подключаем наш новый класс
#include "nextcheckerGameMode.generated.h"

UCLASS(minimalapi)
class ANextcheckerGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ANextcheckerGameMode();

protected:
    virtual void BeginPlay() override;
};

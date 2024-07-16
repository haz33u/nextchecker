#include "nextcheckerGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "MyPlayerController.h"

ANextcheckerGameMode::ANextcheckerGameMode()
{
    PlayerControllerClass = AMyPlayerController::StaticClass();
}

void ANextcheckerGameMode::BeginPlay()
{
    Super::BeginPlay();
}

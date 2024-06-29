#include "nextcheckerGameMode.h"
#include "UObject/ConstructorHelpers.h"

// Похоже, здесь ошибка в имени класса. Должно быть ANextcheckerGameMode, а не AnextcheckerGameMode.
ANextcheckerGameMode::ANextcheckerGameMode()
{
    // Убедитесь, что DefaultPawnClass правильно объявлен в заголовочном файле
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
    DefaultPawnClass = PlayerPawnClassFinder.Class;
}

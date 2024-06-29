#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

// Определяем модуль вашего проекта
class FnextcheckerModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};

IMPLEMENT_PRIMARY_GAME_MODULE(FnextcheckerModule, nextchecker, "nextchecker");

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

UCLASS()
class NEXTCHECKER_API AMyPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AMyPlayerController();

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

    /*
    UFUNCTION(BlueprintCallable, Category = "Network")
    void CreateGameSession();

    UFUNCTION(BlueprintCallable, Category = "Network")
    void FindGames();

    UFUNCTION(BlueprintCallable, Category = "Network")
    void JoinGame();

    void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
    void OnFindSessionsComplete(bool bWasSuccessful);

    private:
    TSharedPtr<FOnlineSessionSearch> SessionSearch;
    */
};

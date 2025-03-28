#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class AMyPlayerController;
UCLASS()
class TASK9_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void OnPostLogin(AController* NewPlayer) override;
	virtual void BeginPlay() override;

	void PrintMessage(AMyPlayerController* ChattingPlayerController, const FString& ChatMessage);
	FString MakeRandomNumber();
	bool IsGuessNumber(const FString& Number);
	FString JudgeResult(const FString& RandomNumber, const FString& Number);
	void IncreaseGuessCount(AMyPlayerController* ChattingPlayerController);
	void ResetGame();
	void JudgeGame(AMyPlayerController* ChattingPlayerController, int StrikeCount);

	AMyPlayerController* GetCurrentTurnPlayerController() const;

protected:
	FString RandomNumberString;
	TArray<TObjectPtr<AMyPlayerController>> AllPlayerControllers;
	FTimerHandle MainTimerHandle;
	int32 CurrentTurnIndex;

private:
	UFUNCTION()
	void OnMainTimerElapsed();
};

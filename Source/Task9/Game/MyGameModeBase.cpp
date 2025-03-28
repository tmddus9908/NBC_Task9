#include "Game/MyGameModeBase.h"

#include "MyGameStateBase.h"
#include "EngineUtils.h"
#include "Player/MyPlayerController.h"
#include "Player/MyPlayerState.h"

void AMyGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(NewPlayer);

	if (IsValid(PlayerController))
	{
		AllPlayerControllers.Add(PlayerController);
		AMyPlayerState* PS = PlayerController->GetPlayerState<AMyPlayerState>();

		if (IsValid(PS))
		{
			PS->PlayerName = TEXT("Player") + FString::FromInt(AllPlayerControllers.Num());
		}

		AMyGameStateBase* MyGameState = GetGameState<AMyGameStateBase>();

		if (IsValid(MyGameState))
		{
			MyGameState->MulticastRPCLoginMessage(PS->PlayerName);
		}

		if (CurrentTurnIndex == AllPlayerControllers.Num() - 1)
		{
			PlayerController->NotificationText = FText::FromString(TEXT("It's your turn"));
		}
		else
		{
			PlayerController->NotificationText = FText::FromString(TEXT("Waiting for other player"));
		}
	}
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	RandomNumberString = MakeRandomNumber();

	GetWorldTimerManager().SetTimer(MainTimerHandle, this, &AMyGameModeBase::OnMainTimerElapsed, 15.f, true);
}

void AMyGameModeBase::PrintMessage(AMyPlayerController* ChattingPlayerController, const FString& ChatMessage)
{
	FString Message = ChatMessage;
	int Index = ChatMessage.Len() - 3;
	FString GuessNumber = ChatMessage.RightChop(Index);

	if (IsGuessNumber(GuessNumber) && ChattingPlayerController == GetCurrentTurnPlayerController())
	{
		FString JudgeResultString = JudgeResult(RandomNumberString, GuessNumber);
		IncreaseGuessCount(ChattingPlayerController);

		for (TActorIterator<AMyPlayerController> It(GetWorld()); It; ++It)
		{
			AMyPlayerController* PlayerController = *It;

			if (IsValid(PlayerController))
			{
				FString CombinedMessage = ChatMessage + TEXT(" -> ") + JudgeResultString;
				PlayerController->ClientRPCPrintMessage(CombinedMessage);

				int32 StrikeCount = FCString::Atoi(*JudgeResultString.Left(1));
				JudgeGame(ChattingPlayerController, StrikeCount);
			}
		}
	}
	else
	{
		for (TActorIterator<AMyPlayerController> It(GetWorld()); It; ++It)
		{
			AMyPlayerController* PlayerController = *It;
			if (IsValid(PlayerController))
			{
				PlayerController->ClientRPCPrintMessage(ChatMessage);
			}
		}
	}
}

FString AMyGameModeBase::MakeRandomNumber()
{
	TArray<int32> Numbers;
	for (int32 i = 1; i <= 9; ++i)
	{
		Numbers.Add(i);
	}

	FMath::RandInit(FDateTime::Now().GetTicks());

	FString Result;
	for (int32 i = 0; i < 3; ++i)
	{
		int32 Index = FMath::RandRange(0, Numbers.Num() - 1);
		Result.Append(FString::FromInt(Numbers[Index]));
		Numbers.RemoveAt(Index);
	}

	return Result;
}

bool AMyGameModeBase::IsGuessNumber(const FString& Number)
{
	bool bCanPlay = false;

	do
	{
		if (Number.Len() != 3)
		{
			break;
		}

		bool bIsUnique = true;
		TSet<TCHAR> UniqueDigits;

		for (TCHAR C : Number)
		{
			if (FChar::IsDigit(C) == false || C == '0')
			{
				bIsUnique = false;
				break;
			}

			UniqueDigits.Add(C);
		}

		if (!bIsUnique)
		{
			break;
		}

		bCanPlay = true;
	}
	while (false);

	return bCanPlay;
}

FString AMyGameModeBase::JudgeResult(const FString& RandomNumber, const FString& Number)
{
	int32 StrikeCount = 0, BallCount = 0;

	for (int32 i = 0; i < 3; ++i)
	{
		if (RandomNumber[i] == Number[i])
		{
			StrikeCount++;
		}
		else
		{
			FString PlayerGuessChar = FString::Printf(TEXT("%c"), RandomNumber[i]);

			if (RandomNumber.Contains(PlayerGuessChar))
			{
				BallCount++;
			}
		}
	}

	if (StrikeCount == 0 && BallCount == 0)
	{
		return TEXT("OUT");
	}

	return FString::Printf(TEXT("%dS%dB"), StrikeCount, BallCount);
}

void AMyGameModeBase::IncreaseGuessCount(AMyPlayerController* ChattingPlayerController)
{
	AMyPlayerState* MyPlayerState = ChattingPlayerController->GetPlayerState<AMyPlayerState>();

	if (IsValid(MyPlayerState))
	{
		MyPlayerState->CurrentGuessCount++;
	}
}

void AMyGameModeBase::ResetGame()
{
	RandomNumberString = MakeRandomNumber();

	for (const auto& MyPlayerController : AllPlayerControllers)
	{
		AMyPlayerState* MyPlayerState = MyPlayerController->GetPlayerState<AMyPlayerState>();

		if (IsValid(MyPlayerState))
		{
			MyPlayerState->CurrentGuessCount = 0;
		}
	}

	CurrentTurnIndex = 0;
}

void AMyGameModeBase::JudgeGame(AMyPlayerController* ChattingPlayerController, int StrikeCount)
{
	if (3 == StrikeCount)
	{
		AMyPlayerState* PlayerState = ChattingPlayerController->GetPlayerState<AMyPlayerState>();

		for (const auto& MyPlayerController : AllPlayerControllers)
		{
			if (IsValid(PlayerState))
			{
				FString CombinedMessageString = PlayerState->PlayerName + TEXT(" has won the game.");
				MyPlayerController->NotificationText = FText::FromString(CombinedMessageString);

				ResetGame();
			}
		}
	}
	else
	{
		bool bIsDraw = true;
		for (const auto& MyPlayerController : AllPlayerControllers)
		{
			AMyPlayerState* PlayerState = MyPlayerController->GetPlayerState<AMyPlayerState>();

			if (IsValid(PlayerState))
			{
				if (PlayerState->CurrentGuessCount < PlayerState->MaxGuessCount)
				{
					bIsDraw = false;
					break;
				}
			}
		}

		if (bIsDraw)
		{
			for (const auto& MyPlayerController : AllPlayerControllers)
			{
				MyPlayerController->NotificationText = FText::FromString(TEXT("Draw"));

				ResetGame();
			}
		}
	}
}

AMyPlayerController* AMyGameModeBase::GetCurrentTurnPlayerController() const
{
	if (AllPlayerControllers.IsEmpty())
	{
		return nullptr;
	}

	if (AllPlayerControllers.IsValidIndex(CurrentTurnIndex))
	{
		return AllPlayerControllers[CurrentTurnIndex];
	}

	return nullptr;
}

void AMyGameModeBase::OnMainTimerElapsed()
{
	if (AllPlayerControllers.Num() == 0)
	{
		return;
	}

	CurrentTurnIndex = (CurrentTurnIndex + 1) % AllPlayerControllers.Num();

	for (int32 i = 0; i < AllPlayerControllers.Num(); ++i)
	{
		if (IsValid(AllPlayerControllers[i]))
		{
			if (i == CurrentTurnIndex)
			{
				AllPlayerControllers[i]->NotificationText = FText::FromString(TEXT("It's your turn"));
			}
			else
			{
				AllPlayerControllers[i]->NotificationText = FText::FromString(TEXT("Waiting for other player"));
			}
		}
	}
}

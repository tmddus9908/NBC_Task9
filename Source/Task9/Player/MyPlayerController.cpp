#include "Player/MyPlayerController.h"

#include "MyPlayerState.h"
#include "Chat/MyUserWidget.h"
#include "Game/MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

AMyPlayerController::AMyPlayerController()
{
	bReplicates = true;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController())
	{
		return;
	}

	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	if (IsValid(TextBoxWidgetClass) == true)
	{
		TextBoxWidgetInstance = CreateWidget<UMyUserWidget>(this, TextBoxWidgetClass);

		if (IsValid(TextBoxWidgetInstance) == true)
		{
			TextBoxWidgetInstance->AddToViewport();
		}
	}

	if (IsValid(NotificationTextWidgetClass))
	{
		NotificationTextWidgetInstance = CreateWidget<UUserWidget>(this, NotificationTextWidgetClass);

		if (IsValid(NotificationTextWidgetInstance))
		{
			NotificationTextWidgetInstance->AddToViewport();
		}
	}
}

void AMyPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, NotificationText);
}

void AMyPlayerController::SetMessage(const FString& Msg)
{
	Message = Msg;

	if (IsLocalController())
	{
		AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();

		if (MyPlayerState)
		{
			FString CombinedMessageString = MyPlayerState->GetPlayerInfoString() + TEXT(": ") + Msg;
			ServerRPCPrintMessage(CombinedMessageString);
		}
	}
}

void AMyPlayerController::PrintMessage(const FString& Msg)
{
	UKismetSystemLibrary::PrintString(this, Msg, true, true, FLinearColor::Blue, 5.0f);
}

void AMyPlayerController::ClientRPCPrintMessage_Implementation(const FString& Msg)
{
	PrintMessage(Msg);
}

void AMyPlayerController::ServerRPCPrintMessage_Implementation(const FString& Msg)
{
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (IsValid(GM))
	{
		AMyGameModeBase* MyGM = Cast<AMyGameModeBase>(GM);

		if (IsValid(MyGM))
		{
			MyGM->PrintMessage(this, Msg);
		}
	}
}

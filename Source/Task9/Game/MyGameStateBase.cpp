#include "MyGameStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayerController.h"

void AMyGameStateBase::MulticastRPCLoginMessage_Implementation(const FString& Name)
{
	if (!HasAuthority())
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		if (IsValid(PC))
		{
			AMyPlayerController* MyPC = Cast<AMyPlayerController>(PC);

			if (IsValid(MyPC))
			{
				FString Notification = Name + TEXT(" has joined the game.");
				MyPC->PrintMessage(Notification);
			}
		}
	}
}

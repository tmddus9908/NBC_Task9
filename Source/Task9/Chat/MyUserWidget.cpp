#include "Chat/MyUserWidget.h"

#include "Player/MyPlayerController.h"

void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!TextBox->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted))
	{
		TextBox->OnTextCommitted.AddDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UMyUserWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (TextBox->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted))
	{
		TextBox->OnTextCommitted.RemoveDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UMyUserWidget::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		APlayerController* PlayerController = GetOwningPlayer();

		if (IsValid(PlayerController))
		{
			AMyPlayerController* PC = Cast<AMyPlayerController>(PlayerController);

			if (IsValid(PC))
			{
				PC->SetMessage(Text.ToString());
				TextBox->SetText(FText());
			}
		}
	}
}

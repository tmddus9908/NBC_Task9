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

void UMyUserWidget::SetNumberText(const FString& Number)
{
	if (IsValid(TextBox))
	{
		TextBox->SetText(FText::FromString(Number));
	}
}

void UMyUserWidget::SetNumberPadText(const FString& Number)
{
	CurrentText = TextBox->GetText().ToString();
	CurrentText.Append(Number);
	TextBox->SetText(FText::FromString(CurrentText));
}

void UMyUserWidget::SetClearTextBox()
{
	if (IsValid(TextBox))
	{
		TextBox->SetText(FText::GetEmpty());
	}
}

void UMyUserWidget::RemoveLastChar()
{
	if (IsValid(TextBox))
	{
		if (!CurrentText.IsEmpty())
		{
			CurrentText.RemoveAt(CurrentText.Len() - 1);
			TextBox->SetText(FText::FromString(CurrentText));
		}
	}
}

void UMyUserWidget::OnSubmitButtonClicked()
{
	SendChatMessage(TextBox->GetText());
}

void UMyUserWidget::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		SendChatMessage(Text);
	}
}

void UMyUserWidget::SendChatMessage(const FText& Text)
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

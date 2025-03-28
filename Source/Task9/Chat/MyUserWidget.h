#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "MyUserWidget.generated.h"

UCLASS()
class TASK9_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void SetNumberText(const FString& Number);
	UFUNCTION()
	void SetNumberPadText(const FString& Number);
	UFUNCTION()
	void SetClearTextBox();
	UFUNCTION()
	void RemoveLastChar();
	UFUNCTION()
	void OnSubmitButtonClicked();
	
	UPROPERTY(meta = (Bindwidget))
	UEditableTextBox* TextBox;
	UPROPERTY()
	FString CurrentText;

protected:
	UFUNCTION()
	void OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	UFUNCTION()
	void SendChatMessage(const FText& Text);
};

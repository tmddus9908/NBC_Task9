#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"


class UNumberUserWidget;
class UMyUserWidget;

UCLASS()
class TASK9_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	void SetMessage(const FString& Msg);
	void PrintMessage(const FString& Msg);

	UFUNCTION(Client, Reliable)
	void ClientRPCPrintMessage(const FString& Msg);
	UFUNCTION(Server, Reliable)
	void ServerRPCPrintMessage(const FString& Msg);

	UPROPERTY(Replicated, BlueprintReadOnly)
	FText NotificationText;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMyUserWidget> TextBoxWidgetClass;
	UPROPERTY()
	UMyUserWidget* TextBoxWidgetInstance;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> NotificationTextWidgetClass;
	UPROPERTY()
	UUserWidget* NotificationTextWidgetInstance;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNumberUserWidget> NumberUserWidgetClass;
	UPROPERTY()
	UNumberUserWidget* NumberUserWidgetInstance;

	FString Message;
};

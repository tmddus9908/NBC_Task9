#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "NumberUserWidget.generated.h"

class UMyUserWidget;

UCLASS()
class TASK9_API UNumberUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetTargetWidget(UMyUserWidget* UserWidget);
	
protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(meta = (BindWidget)) UButton* Button_1;
	UPROPERTY(meta = (BindWidget)) UButton* Button_2;
	UPROPERTY(meta = (BindWidget)) UButton* Button_3;
	UPROPERTY(meta = (BindWidget)) UButton* Button_4;
	UPROPERTY(meta = (BindWidget)) UButton* Button_5;
	UPROPERTY(meta = (BindWidget)) UButton* Button_6;
	UPROPERTY(meta = (BindWidget)) UButton* Button_7;
	UPROPERTY(meta = (BindWidget)) UButton* Button_8;
	UPROPERTY(meta = (BindWidget)) UButton* Button_9;
	UPROPERTY(meta = (BindWidget)) UButton* Button_Reset;
	UPROPERTY(meta = (BindWidget)) UButton* Button_Back;
	UPROPERTY(meta = (BindWidget)) UButton* Button_Submit;

	UFUNCTION()
	void Button_1_Pressed();
	UFUNCTION()
	void Button_2_Pressed();
	UFUNCTION()
	void Button_3_Pressed();
	UFUNCTION()
	void Button_4_Pressed();
	UFUNCTION()
	void Button_5_Pressed();
	UFUNCTION()
	void Button_6_Pressed();
	UFUNCTION()
	void Button_7_Pressed();
	UFUNCTION()
	void Button_8_Pressed();
	UFUNCTION()
	void Button_9_Pressed();
	UFUNCTION()
	void Button_Reset_Pressed();
	UFUNCTION()
	void Button_Back_Pressed();
	UFUNCTION()
	void Button_Submit_Pressed();

	TObjectPtr<UMyUserWidget> MyUserWidget;

};

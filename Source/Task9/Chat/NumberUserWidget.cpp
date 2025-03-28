#include "Chat/NumberUserWidget.h"

#include "MyUserWidget.h"

void UNumberUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_1->OnClicked.AddDynamic(this, &ThisClass::UNumberUserWidget::Button_1_Pressed);
	Button_2->OnClicked.AddDynamic(this, &ThisClass::UNumberUserWidget::Button_2_Pressed);
	Button_3->OnClicked.AddDynamic(this, &ThisClass::UNumberUserWidget::Button_3_Pressed);
	Button_4->OnClicked.AddDynamic(this, &ThisClass::UNumberUserWidget::Button_4_Pressed);
	Button_5->OnClicked.AddDynamic(this, &ThisClass::UNumberUserWidget::Button_5_Pressed);
	Button_6->OnClicked.AddDynamic(this, &ThisClass::UNumberUserWidget::Button_6_Pressed);
	Button_7->OnClicked.AddDynamic(this, &ThisClass::UNumberUserWidget::Button_7_Pressed);
	Button_8->OnClicked.AddDynamic(this, &ThisClass::UNumberUserWidget::Button_8_Pressed);
	Button_9->OnClicked.AddDynamic(this, &ThisClass::UNumberUserWidget::Button_9_Pressed);
	Button_Reset->OnClicked.AddDynamic(this, &ThisClass::UNumberUserWidget::Button_Reset_Pressed);
	Button_Back->OnClicked.AddDynamic(this, &ThisClass::UNumberUserWidget::Button_Back_Pressed);
	Button_Submit->OnClicked.AddDynamic(this, &ThisClass::UNumberUserWidget::Button_Submit_Pressed);
}

void UNumberUserWidget::Button_1_Pressed() { if (MyUserWidget) { MyUserWidget->SetNumberPadText("1"); } }

void UNumberUserWidget::Button_2_Pressed() { if (MyUserWidget) { MyUserWidget->SetNumberPadText("2"); } }

void UNumberUserWidget::Button_3_Pressed() { if (MyUserWidget) { MyUserWidget->SetNumberPadText("3"); } }

void UNumberUserWidget::Button_4_Pressed() { if (MyUserWidget) { MyUserWidget->SetNumberPadText("4"); } }

void UNumberUserWidget::Button_5_Pressed() { if (MyUserWidget) { MyUserWidget->SetNumberPadText("5"); } }

void UNumberUserWidget::Button_6_Pressed() { if (MyUserWidget) { MyUserWidget->SetNumberPadText("6"); } }

void UNumberUserWidget::Button_7_Pressed() { if (MyUserWidget) { MyUserWidget->SetNumberPadText("7"); } }

void UNumberUserWidget::Button_8_Pressed() { if (MyUserWidget) { MyUserWidget->SetNumberPadText("8"); } }

void UNumberUserWidget::Button_9_Pressed() { if (MyUserWidget) { MyUserWidget->SetNumberPadText("9"); } }

void UNumberUserWidget::Button_Reset_Pressed(){ if (MyUserWidget) {MyUserWidget->SetClearTextBox();} }

void UNumberUserWidget::Button_Back_Pressed() { if (MyUserWidget) { MyUserWidget->RemoveLastChar();} }

void UNumberUserWidget::Button_Submit_Pressed() { if (MyUserWidget) { MyUserWidget->OnSubmitButtonClicked();} }

void UNumberUserWidget::SetTargetWidget(UMyUserWidget* UserWidget)
{
	MyUserWidget = UserWidget;
}

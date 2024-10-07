
// Swat Game


#include "UI/SwatHUD.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Game/SwatGameModeBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"


void USwatHUD::NativeConstruct()
{
	if (PauseButton)
	{
		PauseButton->OnClicked.AddDynamic(this, &ThisClass::OnPauseClicked);
	}
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
}

void USwatHUD::InitializeHUD(ASwatGameModeBase* RunGameMode)
{
	if (RunGameMode)
	{
		MedalCount->SetText(FText::AsNumber(0));

		RunGameMode->OnMedalCountChanged.AddDynamic(this, &ThisClass::SetMedalsCount);
	}
}

void USwatHUD::SetMedalsCount(int32 Count)
{
	MedalCount->SetText(FText::AsNumber(Count));

}


void USwatHUD::OnPauseClicked()
{


	if (IsValid(PauseMenuWidgetClass))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		UUserWidget* Widget = CreateWidget(GetWorld(), PauseMenuWidgetClass);
		if (Widget)
		{
			Widget->AddToViewport();
		}
	}
	
}


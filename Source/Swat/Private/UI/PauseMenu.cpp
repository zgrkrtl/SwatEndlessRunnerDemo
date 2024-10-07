// Swat Game


#include "UI/PauseMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UPauseMenu::NativeConstruct()
{
	if (ContinueButton)
	{
		ContinueButton->OnClicked.AddDynamic(this, &ThisClass::OnContinueClicked);
	}

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &ThisClass::OnRestartClicked);
	}


}

void UPauseMenu::OnContinueClicked()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	RemoveFromParent();
}

void UPauseMenu::OnRestartClicked()
{
	UWorld* World = GetWorld();
	if (World) UKismetSystemLibrary::ExecuteConsoleCommand(World, TEXT("RestartLevel"));
}

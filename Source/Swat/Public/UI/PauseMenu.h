// Swat Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class SWAT_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	TObjectPtr<UButton> ContinueButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> RestartButton;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnContinueClicked();

	UFUNCTION()
	void OnRestartClicked();
};

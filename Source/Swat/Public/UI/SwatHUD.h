// Swat Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SwatHUD.generated.h"

class UTextBlock;
class ASwatGameModeBase;
class UButton;
class UUserWidget;

/**
 * 
 */
UCLASS()
class SWAT_API USwatHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	TObjectPtr<UTextBlock> MedalCount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> PauseButton;

	UFUNCTION()
	void OnPauseClicked();

	virtual void NativeConstruct() override;
public:
	UFUNCTION(BlueprintCallable)
	void InitializeHUD(ASwatGameModeBase* RunGameMode);

	UFUNCTION(BlueprintCallable)
	void SetMedalsCount(int32 Count);

	
};

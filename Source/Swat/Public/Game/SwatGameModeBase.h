// Swat Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SwatGameModeBase.generated.h"


class AFloor;
class UUserWidget;
class USwatHUD;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMedalCountChanged, int32, MedalCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLivesCountChanged, int32, LivesCount);


/**
 * 
 */
UCLASS()
class SWAT_API ASwatGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<UUserWidget> GameHUDClass;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<AFloor> FloorTileClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	TObjectPtr<USwatHUD> GameHUD;

	UPROPERTY(VisibleAnywhere)
	int32 TotalMedals = 0;

	UPROPERTY(VisibleAnywhere)
	int32 NumOfLives = 0;

	UPROPERTY(EditAnywhere)
	int32 MaxLives = 0;

	UPROPERTY(EditAnywhere, Category = "Config")
	int32 InitialFloorTiles = 10;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	FTransform NextSpawnPoint;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	TArray<float> LaneSwitchValues;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FOnMedalCountChanged OnMedalCountChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FOnLivesCountChanged OnLivesCountChanged;

	UFUNCTION(BlueprintCallable)
	void InitializeFloorTiles();

	UFUNCTION(BlueprintCallable)
	AFloor* AddFloorTile(const bool bSpawnItems);	

	UFUNCTION(BlueprintCallable)
	void AddMedal();
protected:
	virtual void BeginPlay() override;
	
};

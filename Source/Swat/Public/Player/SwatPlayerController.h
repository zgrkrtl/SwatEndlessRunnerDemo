// Swat Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SwatPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class ASwatGameModeBase;
/**
 * 
 */
UCLASS()
class SWAT_API ASwatPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASwatPlayerController();

	UFUNCTION(BlueprintImplementableEvent, Category = "Lane")
	void ChangeLane();

	UFUNCTION(BlueprintCallable, Category = "Lane")
	void ChangeLaneUpdate(const float Val);

	UFUNCTION(BlueprintCallable, Category = "Lane")
	void ChangeLaneFinished();

	UFUNCTION(BlueprintCallable, Category = "Lane")
	int32 WhichLane();

	UFUNCTION(BlueprintCallable, Category = "Lane")
	int32 GetPreviousLane();

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	int32 CurrentLane = 1;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	int32 NextLane = 0;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	int32 CurrentLaneRightNow = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveDownImpulse = -1000.f;

	void DisableInput();
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void Jump();
	void StopJump();
	void Shoot();
	void MoveLeft();
	void MoveRight();
	void MoveDown();

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> SwatContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveLeftAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveRightAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveDownAction;

	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<ASwatGameModeBase> GameMode;

	int32 PreviousLane = 2; // Default lane, assuming middle lane is 2

};

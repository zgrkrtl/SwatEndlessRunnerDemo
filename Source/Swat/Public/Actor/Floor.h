// Swat Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "Floor.generated.h"


class UBoxComponent;
class USceneComponent;
class UStaticMeshComponent;
class ASwatGameModeBase;
class AObstacle;
class AMedal;

UCLASS()
class SWAT_API AFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	AFloor();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	TSubclassOf<AObstacle> SmallObstacleClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	TSubclassOf<AObstacle> BigObstacleClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	TSubclassOf<AMedal> MedalClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* FloorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* AttachPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* CenterLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* RightLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* LeftLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* FloorTriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	float SpawnPercent1 = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	float SpawnPercent2 = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	float SpawnPercent3 = 0.5f;

	UFUNCTION(BlueprintCallable)
	void SpawnItems();

	FORCEINLINE const FTransform& GetAttachTransform() const
	{
		return AttachPoint->GetComponentTransform();
	}	
protected:
	UPROPERTY(VisibleInstanceOnly)
	ASwatGameModeBase* SwatGameMode;

	UFUNCTION()
	void OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SpawnLaneItem(UArrowComponent* Lane);
	
	UFUNCTION()
	void DestroyFloorTile();

	UPROPERTY()
	FTimerHandle DestroyHandle;
};

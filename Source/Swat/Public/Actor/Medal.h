// Swat Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Medal.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class USphereComponent;
class URotatingMovementComponent;
class USoundBase;
class UNiagaraComponent;

UCLASS()
class SWAT_API AMedal : public AActor
{
	GENERATED_BODY()
	
public:	
	AMedal();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr< USceneComponent> SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr< UStaticMeshComponent> MedalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr< USphereComponent> SphereCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr< URotatingMovementComponent> RotatingMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Assets")
	TObjectPtr< USoundBase> OverlapSound;
};

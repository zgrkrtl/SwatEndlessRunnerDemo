// Swat Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SwatCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UParticleSystem;
class ASwatGameModeBase;
class APlayerStart;
UCLASS()
class SWAT_API ASwatCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASwatCharacter();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Death();

	UFUNCTION()
	void AddMedal();
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDeath();

	UPROPERTY()
	FTimerHandle RestartTimerHandle;

	UPROPERTY()
	bool bIsDead=false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Assets")
	TObjectPtr<USoundBase> DeathSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, Category = "Spring Arm")
	float SpringArmTargetLength = 500.f;

	


private:
	void Run();

	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<ASwatGameModeBase> RunGameMode;
	
};

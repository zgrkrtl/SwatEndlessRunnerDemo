// Swat Game


#include "Character/SwatCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Game/SwatGameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "Player/SwatPlayerController.h"

ASwatCharacter::ASwatCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->TargetArmLength = SpringArmTargetLength;
	SpringArm->SocketOffset = FVector(0.f, 0.f, 250.f);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm);

	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

}

void ASwatCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Endless Runner
	Run();
}

void ASwatCharacter::BeginPlay()
{
	Super::BeginPlay();	


	RunGameMode = Cast<ASwatGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	check(RunGameMode);
	
}

void ASwatCharacter::Death()
{
	
	if(!bIsDead)
	{
		
		UWorld* World = GetWorld();
		if (DeathMontage && DeathSound && World)
		{
			//handle death
			const FVector Location = GetActorLocation();
			bIsDead = true;

			ASwatPlayerController* PC = Cast<ASwatPlayerController>(GetController());
			if (PC) PC->DisableInput();
			GetCharacterMovement()->MaxWalkSpeed = 0.f;
			UGameplayStatics::PlaySoundAtLocation(World, DeathSound, Location);
			PlayAnimMontage(DeathMontage);
			World->GetTimerManager().SetTimer(RestartTimerHandle, this, &ThisClass::OnDeath, 2.5f);
		}
		
	}
	
}

void ASwatCharacter::AddMedal()
{
	RunGameMode->AddMedal();
}

void ASwatCharacter::OnDeath()
{
	//avoid repetition of death function by bool check
	bIsDead = false;
	if (RestartTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(RestartTimerHandle);
	}
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("RestartLevel"));
}

void ASwatCharacter::Run()
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Roll = 0.f;
	ControlRotation.Pitch = 0.f;

	ControlRotation.Yaw += 180.0f;
	AddMovementInput(ControlRotation.Vector());
}



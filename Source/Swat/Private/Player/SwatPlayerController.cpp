// Swat Game


#include "Player/SwatPlayerController.h"
#include "Character/SwatCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Game/SwatGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/PlayerController.h"


ASwatPlayerController::ASwatPlayerController()
{
}

void ASwatPlayerController::DisableInput()
{
    SetIgnoreMoveInput(true);  // Disables movement input
    SetIgnoreLookInput(true);  // Disables look (mouse rotation) input
}

void ASwatPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // settings for  Enhanced Input System
    check(SwatContext);

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    check(Subsystem);

    // define mapping context to use
    Subsystem->AddMappingContext(SwatContext, 0);

    // some screen settings
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;
    SetInputMode(FInputModeGameAndUI());

    GameMode = Cast<ASwatGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
    //Check: if fails -> crash
    check(GameMode);
}

void ASwatPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASwatPlayerController::Jump);
    EnhancedInputComponent->BindAction(MoveLeftAction, ETriggerEvent::Triggered, this, &ASwatPlayerController::MoveLeft);
    EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ASwatPlayerController::MoveRight);
    EnhancedInputComponent->BindAction(MoveDownAction, ETriggerEvent::Triggered, this, &ASwatPlayerController::MoveDown);
    //InputComponent->BindAction("Shoot", IE_Pressed, this, &ASwatPlayerController::Shoot);

}

void ASwatPlayerController::Jump()
{  
    if (ASwatCharacter* SwatCharacter = Cast<ASwatCharacter>(GetCharacter()))
    {
        SwatCharacter->Jump();
    }
}

void ASwatPlayerController::StopJump()
{
    if (ASwatCharacter* SwatCharacter = Cast<ASwatCharacter>(GetCharacter()))
    {
        SwatCharacter->StopJumping();
    }
}

void ASwatPlayerController::MoveLeft()
{
    NextLane = FMath::Clamp(CurrentLane - 1, 0, 2);
    ChangeLane();
}

void ASwatPlayerController::MoveRight()
{
    NextLane = FMath::Clamp(CurrentLane + 1, 0, 2);
    ChangeLane();
}

void ASwatPlayerController::MoveDown()
{
    if (ASwatCharacter* SwatCharacter = Cast<ASwatCharacter>(GetCharacter()))
    {
        static FVector Impulse = FVector(0, 0, MoveDownImpulse);
        SwatCharacter->GetCharacterMovement()->AddImpulse(Impulse, true);
    }
}

void ASwatPlayerController::Shoot()
{
}

void ASwatPlayerController::ChangeLaneUpdate(const float Val)
{
    if (ASwatCharacter* SwatCharacter = Cast<ASwatCharacter>(GetCharacter()))
    {
        FVector Location = SwatCharacter->GetCapsuleComponent()->GetComponentLocation();
        Location.Y = FMath::Lerp(GameMode->LaneSwitchValues[CurrentLane], GameMode->LaneSwitchValues[NextLane],Val);
        SwatCharacter->SetActorLocation(Location);
    }
}

void ASwatPlayerController::ChangeLaneFinished()
{
    CurrentLane = NextLane;
}

int32 ASwatPlayerController::WhichLane()
{
    if (ASwatCharacter* SwatCharacter = Cast<ASwatCharacter>(GetCharacter()))
    {
        FVector Location = SwatCharacter->GetCapsuleComponent()->GetComponentLocation();
        // Store the current lane before we return it
        PreviousLane = CurrentLaneRightNow;

        if (Location.Y == 0.f)
        {
            CurrentLaneRightNow = 2;
        }
        else if (Location.Y < 0.f)
        {
            CurrentLaneRightNow = 1;
        }
        else
        {
            CurrentLaneRightNow = 3;
        }
        return CurrentLaneRightNow;
    }
    return 0;
}

int32 ASwatPlayerController::GetPreviousLane()
{
    return PreviousLane;
}


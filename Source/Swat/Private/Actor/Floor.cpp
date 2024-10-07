// Swat Game


#include "Actor/Floor.h"
#include "Actor/Obstacle.h"
#include "Game/SwatGameModeBase.h"
#include "Character/SwatCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actor/Medal.h"

AFloor::AFloor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	FloorMesh->SetupAttachment(SceneComponent);

	AttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Attach Point"));
	AttachPoint->SetupAttachment(SceneComponent);

	CenterLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Center Lane"));
	CenterLane->SetupAttachment(SceneComponent);

	RightLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Right Lane"));
	RightLane->SetupAttachment(SceneComponent);

	LeftLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Left Lane"));
	LeftLane->SetupAttachment(SceneComponent);

	FloorTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Floor Trigger Box"));
	FloorTriggerBox->SetupAttachment(SceneComponent);
	FloorTriggerBox->SetBoxExtent(FVector(32.f, 500.f, 200.f));
	FloorTriggerBox->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	
}

void AFloor::BeginPlay()
{
	Super::BeginPlay();

	SwatGameMode = Cast<ASwatGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	//Check: if fails -> crash
	check(SwatGameMode);

	FloorTriggerBox->OnComponentBeginOverlap.AddDynamic(this,&AFloor::OnTriggerBoxOverlap);
}




void AFloor::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASwatCharacter* SwatCharacter = Cast<ASwatCharacter>(OtherActor);
	if (SwatCharacter)
	{
		SwatGameMode->AddFloorTile(true);

		GetWorldTimerManager().SetTimer(DestroyHandle, this, &ThisClass::DestroyFloorTile , 2.f,false);
	}
}

void AFloor::SpawnItems()
{
	if(IsValid(SmallObstacleClass) && IsValid(BigObstacleClass) && IsValid(MedalClass))
	{
		SpawnLaneItem(CenterLane);
		SpawnLaneItem(LeftLane);
		SpawnLaneItem(RightLane);
	}
}

void AFloor::SpawnLaneItem(UArrowComponent* Lane)
{
	const float RandVal = FMath::FRandRange(0.f, 1.f);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	const FTransform& SpawnLocation = Lane->GetComponentTransform();

	if (UKismetMathLibrary::InRange_FloatFloat(RandVal, SpawnPercent1, SpawnPercent2, true, true))
	{
		AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(SmallObstacleClass, SpawnLocation, SpawnParameters);
	}
	else if(UKismetMathLibrary::InRange_FloatFloat(RandVal, SpawnPercent2, SpawnPercent3, true, true))
	{
		AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(BigObstacleClass, SpawnLocation, SpawnParameters);

	}
	else if (UKismetMathLibrary::InRange_FloatFloat(RandVal, SpawnPercent3, 1.f, true, true))
	{
		AMedal* Medal = GetWorld()->SpawnActor<AMedal>(MedalClass, SpawnLocation, SpawnParameters);
	}
} 

void AFloor::DestroyFloorTile()
{
	if (DestroyHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(DestroyHandle);
	}
	Destroy();
}
 

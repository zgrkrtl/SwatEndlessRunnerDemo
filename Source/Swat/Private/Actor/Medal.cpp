// Swat Game


#include "Actor/Medal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/SwatCharacter.h"

AMedal::AMedal()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(SceneComponent);
	SphereCollider->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	MedalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MedalMesh"));
	MedalMesh->SetupAttachment(SphereCollider);
	MedalMesh->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	RotatingMovement->RotationRate = FRotator(0, 180, 0);

}

void AMedal::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereOverlap);
}

void AMedal::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASwatCharacter* SwatCharacter = Cast<ASwatCharacter>(OtherActor))
	{
		if (OverlapSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), OverlapSound, GetActorLocation());
		}
		SwatCharacter->AddMedal();

		Destroy();
	}
}



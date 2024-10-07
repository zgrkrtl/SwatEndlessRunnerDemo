// Swat Game

#include "Game/SwatGameModeBase.h"
#include "Actor/Floor.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "UI/SwatHUD.h"

void ASwatGameModeBase::BeginPlay()
{
	GameHUD = Cast<USwatHUD>(CreateWidget(GetWorld(), GameHUDClass));
	check(GameHUD);

	GameHUD->InitializeHUD(this);
	GameHUD->AddToViewport();
	InitializeFloorTiles();
}


void ASwatGameModeBase::InitializeFloorTiles()
{ 
	AFloor* Tile = AddFloorTile(false);

	if (Tile)
	{
		LaneSwitchValues.Add(Tile->LeftLane->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->CenterLane->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->RightLane->GetComponentLocation().Y);
	}
	AddFloorTile(false);
	AddFloorTile(false);
	AddFloorTile(false);
	
	for (int i = 0; i < InitialFloorTiles; i++)
	{
		AddFloorTile(true);
	}
}

AFloor* ASwatGameModeBase::AddFloorTile(const bool bSpawnItems)
{
	if (GetWorld())
	{
		AFloor* FloorTile = GetWorld()->SpawnActor<AFloor>(FloorTileClass, NextSpawnPoint);
		if (FloorTile)
		{
			if (bSpawnItems)
			{
				FloorTile->SpawnItems();
			}

			NextSpawnPoint = FloorTile->GetAttachTransform();
		}
		return FloorTile;
	}
	return nullptr;
}

void ASwatGameModeBase::AddMedal()
{
	TotalMedals++;
	OnMedalCountChanged.Broadcast(TotalMedals);
}

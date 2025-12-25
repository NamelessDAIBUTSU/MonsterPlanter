// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/IngameGameMode.h"
#include <Room/RoomManager.h>

AIngameGameMode::AIngameGameMode()
{
}

void AIngameGameMode::StartPlay()
{
	Super::StartPlay();

	// デフォルトで存在させる部屋を生成
	if (URoomManager* RoomManager = GetWorld()->GetSubsystem<URoomManager>())
	{
		RoomManager->CreateDefaultRooms();
	}
}

void AIngameGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "Room/RoomBase.h"
#include <Room/RoomDef.h>
#include "Components/PointLightComponent.h"
#include <Camera/RoomCamera.h>
#include <Kismet/GameplayStatics.h>
#include <PlayerController/GodPlayerController.h>
#include <Camera/CameraManager.h>
#include <Camera/CameraComponent.h>
#include <Room/RoomManager.h>
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"


ARoomBase::ARoomBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// 部屋の原点を設定
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RoomRoot"));

}

void ARoomBase::BeginPlay()
{
	Super::BeginPlay();

	// ルームマネージャーに登録
	if (URoomManager* RoomManager = GetWorld()->GetSubsystem<URoomManager>())
	{
		RoomManager->AddRoom(this);
	}
}

void ARoomBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// リスポーン地点の取得
FVector ARoomBase::GetRespawnLocation() const 
{
	return IsValid(RespawnPoint) ? RespawnPoint->GetActorLocation() : FVector();
}

void ARoomBase::AddFloorTile(AFloorTile* Tile)
{
	FloorTiles.Add(Tile);
}

void ARoomBase::AddWallTile(AWallTile* Tile)
{
	WallTiles.Add(Tile);
}

void ARoomBase::AddRoofTile(AFloorTile* Tile)
{
	RoofTiles.Add(Tile);
}

// ドア開閉シーケンスの再生
void ARoomBase::PlayDoorOpenSequence()
{
	if (IsValid(LevelSequenceActor) && IsValid(LevelSequenceActor->SequencePlayer))
	{
		LevelSequenceActor->SequencePlayer->Play();
	}
}


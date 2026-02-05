// Fill out your copyright notice in the Description page of Project Settings.

#include "Room/RoomBase.h"
#include <Room/RoomDef.h>
#include "Components/PointLightComponent.h"
#include <Kismet/GameplayStatics.h>
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

// シーケンスの再生
void ARoomBase::PlaySequenceImpl(ALevelSequenceActor* LSA)
{
	if (IsValid(LSA) && IsValid(LSA->SequencePlayer))
	{
		LSA->SequencePlayer->Play();
	}
}

// ドア開閉シーケンスの再生
void ARoomBase::PlayDoorOpenSequence()
{
	PlaySequenceImpl(LSA_DoorOpen);
}

// 落下シーケンスの再生
void ARoomBase::PlayFallSequence()
{
	PlaySequenceImpl(LSA_Fall);
}

// プレイヤーをリスポーンさせる
void ARoomBase::OnRespawnPlayer()
{
	// プレイヤーの取得
	AActor* PlayerBody = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerBody == nullptr)
		return;


	// 落下したプレイヤーを復活ポイントに戻す
	PlayerBody->SetActorLocation(GetRespawnLocation());

	// プレイヤーに固定落下ダメージを与える

}


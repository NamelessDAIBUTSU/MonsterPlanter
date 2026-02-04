// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomLayoutData.h"
#include "Tile/FloorTile.h"
#include "Tile/WallTile.h"
#include "Tile/RoofTile.h"
#include <Room/RoomDef.h>
#include "RoomBase.generated.h"

UCLASS()
class MONSTERPLANTER_API ARoomBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ARoomBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	// 部屋ID
	int32 GetRoomID() const { return RoomID; }
	void SetRoomID(int32 Id) { RoomID = Id; }

	// リスポーン地点の取得
	FVector GetRespawnLocation() const;

	// 床タイルの追加
	void AddFloorTile(AFloorTile* Tile);
	// 壁タイルの追加
	void AddWallTile(AWallTile* Tile);
	// 天井タイルの追加
	void AddRoofTile(AFloorTile* Tile);


private: /* オブジェクト */
	// 床タイルオブジェクトの配列
	UPROPERTY()
	TArray<TObjectPtr<AFloorTile>> FloorTiles;
	// 壁タイルオブジェクトの配列
	UPROPERTY()
	TArray<TObjectPtr<AWallTile>> WallTiles;
	// 天井タイルオブジェクトの配列
	UPROPERTY()
	TArray<TObjectPtr<AFloorTile>> RoofTiles;

	// 部屋の状態
	UPROPERTY(VisibleAnywhere)
	ERoomState RoomState = ERoomState::InActive;

	// 部屋ID
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 RoomID = INDEX_NONE;

	// リスポーン地点
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> RespawnPoint;
};

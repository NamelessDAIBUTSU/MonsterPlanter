// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomLayoutData.h"
#include "Tile/FloorTile.h"
#include "Tile/WallTile.h"
#include "Tile/RoofTile.h"
#include "RoomBase.generated.h"

// 魔王城の部屋の基本クラス
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

	// グリッド線の表示切替
	void ToggleVisibleGrid();

protected:
	// 部屋毎の専用初期化
	virtual void InitializeRoom() {}

	// 床の配置
	virtual void SetupFloor();
	// 壁の配置
	virtual void SetupWalls();
	// 天井の配置
	virtual void SetupRoof();

	// ライトを配置
	virtual void SetupLights();
	// メインライトを配置
	virtual void SetupMainLight();
	// 補助ライトを配置
	virtual void SetupSubLights();
	// 演出ライトを配置
	virtual void SetupDecorationLight();

	// カメラを天井の左下（X=0, Y=Height-1）のすぐ下に配置する
	virtual void SetupCamera();

private:
	// タイルの数を初期化
	void InitializeTileCounts();

	// 部屋のレイアウトに基づいてモジュールを配置
	void SetupRoomLayout();

public:
	// 床配置用の親コンポーネント
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> FloorRootComp = nullptr;

	// 壁配置用の親コンポーネント
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> WallRootComp = nullptr;

	// 天井配置用の親コンポーネント
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> RoofRootComp = nullptr;

private:
	// 部屋のレイアウト情報
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URoomLayoutData> LayoutData = nullptr;

	// 部屋ID
	UPROPERTY(VisibleAnywhere)
	int32 RoomID = INDEX_NONE;

	// 床タイルの数
	int32 FloorTileWidth = 0;
	int32 FloorTileHeight = 0;

	// 壁タイルの数
	int32 UDWallTileWidth = 0;
	int32 UDWallTileHeight = 0;
	int32 LRWallTileWidth = 0;
	int32 LRWallTileHeight = 0;

	// 天井タイルの数
	int32 RoofTileWidth = 0;
	int32 RoofTileHeight = 0;

	// 床タイルオブジェクトの配列
	UPROPERTY()
	TArray<TObjectPtr<AFloorTile>> FloorTiles;

	// 壁タイルオブジェクトの配列
	UPROPERTY()
	TArray<TObjectPtr<AWallTile>> WallTiles;
	
	// 天井タイルオブジェクトの配列
	UPROPERTY()
	TArray<TObjectPtr<ARoofTile>> RoofTiles;

	// 前後に繋がっている部屋
	UPROPERTY()
	TObjectPtr<ARoomBase> NextRoom = nullptr;
	UPROPERTY()
	TObjectPtr<ARoomBase> PreRoom = nullptr;

	// 部屋カメラ
	UPROPERTY()
	TObjectPtr<class ARoomCamera> RoomCamera = nullptr;
};

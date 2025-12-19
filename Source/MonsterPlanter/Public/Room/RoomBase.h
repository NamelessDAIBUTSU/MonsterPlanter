// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomLayoutData.h"
#include "FloorTile.h"
#include "WallTile.h"
#include "RoofTile.h"
#include "Camera/CameraComponent.h"
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

private:
	// 部屋のレイアウトに基づいてモジュールを配置
	void SetupRoomLayout();
	// 床の配置
	void SetupFloor();
	// 壁の配置
	void SetupWalls();
	// 天井の配置
	void SetupRoof();

	// ライトを配置
	void SetupLights();
	// メインライトを配置
	void SetupMainLight();
	// 補助ライトを配置
	void SetupSubLights();
	// 演出ライトを配置
	void SetupDecorationLight();

	// タイルの数を初期化
	void InitializeTileCounts();

	// カメラを天井の左下（X=0, Y=Height-1）のすぐ下に配置する
	void SetupCamera();

public:
	// 部屋のレイアウト情報
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	URoomLayoutData* LayoutData = nullptr;

	// 床配置用の親コンポーネント
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* FloorRootComp = nullptr;

	// 壁配置用の親コンポーネント
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* WallRootComp = nullptr;

	// 天井配置用の親コンポーネント
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* RoofRootComp = nullptr;

	// カメラを天井からどれだけ下げるか
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraDistanceBelowRoof = 50.f;


private:
	// 床タイルの数
	UPROPERTY()
	int32 FloorTileWidth = 0;
	int32 FloorTileHeight = 0;

	// 壁タイルの数
	UPROPERTY()
	int32 UDWallTileWidth = 0;
	int32 UDWallTileHeight = 0;
	int32 LRWallTileWidth = 0;
	int32 LRWallTileHeight = 0;

	// 天井タイルの数
	UPROPERTY()
	int32 RoofTileWidth = 0;
	int32 RoofTileHeight = 0;

	// 床タイルオブジェクトの配列
	UPROPERTY()
	TArray<AFloorTile*> FloorTiles;

	// 壁タイルオブジェクトの配列
	UPROPERTY()
	TArray<AWallTile*> WallTiles;
	
	// 天井タイルオブジェクトの配列
	UPROPERTY()
	TArray<ARoofTile*> RoofTiles;

	// 繋がっている次の部屋
	UPROPERTY()
	ARoomBase* NextRoom = nullptr;

	// 部屋カメラ
	UPROPERTY()
	class ARoomCamera* RoomCamera = nullptr;
};

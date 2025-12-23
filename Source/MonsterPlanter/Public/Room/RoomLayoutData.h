// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Tile/FloorTile.h"
#include "Tile/WallTile.h"
#include "Tile/RoofTile.h"
#include "RoomLayoutData.generated.h"

/// <summary>
/// 1行の床データ
/// </summary>
USTRUCT(BlueprintType)
struct FFloorRow
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AFloorTile>> RowCells;
};

/// <summary>
/// 部屋データ
/// </summary>
UCLASS()
class MONSTERPLANTER_API URoomLayoutData : public UDataAsset
{
	GENERATED_BODY()
	
public: /* 部屋の基本情報 */
	// 部屋の名前
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName RoomName;

	// 部屋の説明文
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = true))
	FString RoomDescription;

	// 天井までの高さ
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RoomHeight = 1000.f;

	// モンスターの配置可能数
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxMonsterCount = 5;

public: /* モジュール */
	// 床
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Modules")
	TArray<FFloorRow> FloorTiles;

	// 壁
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Modules")
	TSubclassOf<AWallTile> WallClass;

	// 天井
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Modules")
	TSubclassOf<ARoofTile> RoofClass;

	// 初期配置される装飾
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Modules")
	TArray<TSubclassOf<AActor>> InitialDecorations;


public: /* ライト情報 */
	// 配置オフセット
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Light")
	float LightZOffset = 50.0f;

	// 光量
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Light")
	float MainLightIntensity = 3000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Light")
	float SubLightIntensity = 1500.0f;

	// 半径
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Light")
	float MainLightRadius = 800.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Light")
	float SubLightRadius = 800.0f;

	// 光の色
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Light")
	FLinearColor MainLightColor = FLinearColor::White;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Light")
	FLinearColor SubLightColor = FLinearColor::White;

public: /* カメラ情報 */
	// FOV
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float CameraFOV = 90.0f;

public: /* 配置情報 */
	// 装飾の位置
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout")
	TArray<FTransform> DecorationTransforms;

	// 配置スロットの位置
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout")
	TArray<FTransform> FreeSlotTransforms;

	// モンスターの配置スロットの位置
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout")
	TArray<FTransform> MonsterSlotTransforms;

	// プレイヤーの入口/出口位置
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout")
	FTransform PlayerEntryTransform;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout")
	FTransform PlayerExitTransform;

};

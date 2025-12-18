// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RoomLayoutData.generated.h"

/**
 * 
 */
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

	// 部屋のサイズ
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector RoomSize;

public: /* 使用するモジュールの種類 */
	// 床
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Modules")
	TSubclassOf<AActor> FloorClass;

	// 壁
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Modules")
	TSubclassOf<AActor> WallClass;

	// 天井
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Modules")
	TSubclassOf<AActor> RoofClass;

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

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <FarmSlot/FarmSlotBase.h>
#include "FarmlandBase.generated.h"

/// <summary>
/// 栽培場の基本クラス
/// </summary>
UCLASS()
class MONSTERPLANTER_API AFarmlandBase : public AActor
{
	GENERATED_BODY()

public:
	AFarmlandBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	// 栽培区画の生成
	void CreateFarmSlots();


public:
	// 栽培場のメインメッシュ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshComp = nullptr;

	// 生成する栽培区画の基本クラス
	UPROPERTY(EditAnywhere)
	TSubclassOf<AFarmSlotBase> FarmSlotClass;

	// 栽培区画の横方向の個数
	UPROPERTY(EditAnywhere)
	int FarmSlotWidthNum = 3;

	// 栽培区画の縦方向の個数
	UPROPERTY(EditAnywhere)
	int FarmSlotHeightNum = 2;

	// 栽培場上下左右のマージン(cm)
	UPROPERTY(EditAnywhere)
	float Margin = 600.f;

	// 栽培区画間のマージン
	UPROPERTY(EditAnywhere)
	float SlotWidthMargin = 300.f;
	UPROPERTY(EditAnywhere)
	float SlotHeightMargin = 150.f;

protected:
	// 栽培区画リスト
	UPROPERTY(BlueprintReadOnly)
	TArray<AFarmSlotBase*> FarmSlots;

	// 栽培区画のメッシュサイズ
	FVector SlotMeshExtent = FVector::Zero();
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <FarmSlot/FarmslotDef.h>
#include "FarmSlotBase.generated.h"

/// <summary>
/// 栽培区画の基本クラス
/// </summary>
UCLASS()
class MONSTERPLANTER_API AFarmSlotBase : public AActor
{
	GENERATED_BODY()

public:
	AFarmSlotBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaTime) override;

public:
	// 栽培可能コスト
	UPROPERTY(EditAnywhere)
	int32 MaxCost;

	// 特性タイプ
	UPROPERTY(EditAnywhere)
	EFarmSlotBuffType BuffType;

	// 特性パラメータ
	UPROPERTY(EditAnywhere)
	int32 FeatureParam;

private:
	// 栽培区画のメインメッシュ
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComp;

	// 区画サイズ
	UPROPERTY(VisibleAnywhere)
	FVector2D SlotSize = FVector2D();

	// 経験値
};

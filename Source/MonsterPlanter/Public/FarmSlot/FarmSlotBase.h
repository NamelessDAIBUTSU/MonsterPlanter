// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	virtual void Tick(float DeltaTime) override;

public:
	// 栽培区画のメインメッシュ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshComp = nullptr;
};

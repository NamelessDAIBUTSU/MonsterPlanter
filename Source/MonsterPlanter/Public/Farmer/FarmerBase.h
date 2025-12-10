// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FarmerBase.generated.h"

/// <summary>
/// 栽培員の基本クラス
/// </summary>
UCLASS()
class MONSTERPLANTER_API AFarmerBase : public ACharacter
{
	GENERATED_BODY()
	
public:	
	AFarmerBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	// 周回速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Farmer Properties")
	float MoveSpeed = 600.f;

	// 育てアクションの速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Farmer Properties")	
	float FeedSpeed = 200.f;
};

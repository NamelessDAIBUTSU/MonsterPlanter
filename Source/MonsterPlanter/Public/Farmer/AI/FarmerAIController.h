// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FarmerAIController.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERPLANTER_API AFarmerAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	// コンストラクタ
	AFarmerAIController();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TObjectPtr<class UBehaviorTree> BehaviorTreeAsset = nullptr;
};

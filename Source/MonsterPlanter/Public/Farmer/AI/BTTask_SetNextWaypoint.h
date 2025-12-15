// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetNextWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERPLANTER_API UBTTask_SetNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	// タスク実行関数のオーバーライド
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

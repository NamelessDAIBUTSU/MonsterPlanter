// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MoveToWaypoint.generated.h"

// NodeMemory 用のシンプルな POD 構造体にする（USTRUCT を使わない）
struct FMoveToWayPointMemory
{
	// 移動速度
	FVector MoveSpeed = FVector::Zero();
};

UCLASS()
class MONSTERPLANTER_API UBTTask_MoveToWaypoint : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_MoveToWaypoint();

	// タスク実行関数のオーバーライド
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// Tick を受け取るためのオーバーライド
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	// NodeMemory のサイズを返す（必須）
	virtual uint16 GetInstanceMemorySize() const override;

private:

};

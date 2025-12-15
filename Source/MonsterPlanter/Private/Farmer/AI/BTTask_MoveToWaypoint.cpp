// Fill out your copyright notice in the Description page of Project Settings.


#include "Farmer/AI/BTTask_MoveToWaypoint.h"
#include <Farmer/FarmerBase.h>
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Farmland/FarmlandBase.h"
#include "AIController.h"

UBTTask_MoveToWaypoint::UBTTask_MoveToWaypoint()
{
	// Tick を受け取り、タスク名を設定
	bNotifyTick = true;
	NodeName = TEXT("MoveToWaypoint");
}

uint16 UBTTask_MoveToWaypoint::GetInstanceMemorySize() const
{
	return sizeof(FMoveToWayPointMemory);
}

EBTNodeResult::Type UBTTask_MoveToWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
		return EBTNodeResult::Failed;

	// コンポーネントから栽培員キャラクターを取得
	AFarmerBase* Farmer = AIController->GetPawn<AFarmerBase>();
	if (Farmer == nullptr)
		return EBTNodeResult::Failed;

	// 対応する栽培場を取得
	AFarmlandBase* Farmland = Farmer->GetAssignedFarmland();
	if (Farmland == nullptr)
		return EBTNodeResult::Failed;

	// ウェイポイント配列を取得
	const TArray<FWaypoint>& Waypoints = Farmland->GetWaypoints();

	// NodeMemory が正しく渡されているかチェック
	if (NodeMemory == nullptr)
		return EBTNodeResult::Failed;

	FMoveToWayPointMemory* MyMemory = reinterpret_cast<FMoveToWayPointMemory*>(NodeMemory);
	if (MyMemory == nullptr)
		return EBTNodeResult::Failed;

	// 移動先ウェイポイントを取得
	FWaypoint TargetWaypoint = Farmer->GetTargetWaypoint();

	// 毎フレーム移動する速度を計算して保存
	MyMemory->MoveSpeed = (TargetWaypoint.WaypointLocation - Farmer->GetActorLocation()).GetSafeNormal() * Farmer->MoveSpeed;

	return EBTNodeResult::InProgress;
}

// 移動更新
void UBTTask_MoveToWaypoint::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
		return;

	AFarmerBase* Farmer = AIController->GetPawn<AFarmerBase>();
	if (Farmer == nullptr)
		return;

	if (NodeMemory == nullptr)
		return;

	FMoveToWayPointMemory* MyMemory = reinterpret_cast<FMoveToWayPointMemory*>(NodeMemory);
	if (MyMemory == nullptr)
		return;

	// 移動更新
	FVector NewLocation = Farmer->GetActorLocation() + MyMemory->MoveSpeed * DeltaSeconds;
	Farmer->SetActorLocation(NewLocation);

	// XY 平面上での距離を計算して完了判定を行う
	FWaypoint TargetWaypoint = Farmer->GetTargetWaypoint();
	FVector NewLocationXY = FVector(NewLocation.X, NewLocation.Y, 0.f);
	FVector TargetLocationXY = FVector(TargetWaypoint.WaypointLocation.X, TargetWaypoint.WaypointLocation.Y, 0.f);

	// 10 ユニット以内で到達とみなす
	const float AcceptRadiusSq = FMath::Square(2.0f); 
	if ((NewLocationXY - TargetLocationXY).SizeSquared() <= AcceptRadiusSq)
	{
		Farmer->SetActorLocation(TargetWaypoint.WaypointLocation);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

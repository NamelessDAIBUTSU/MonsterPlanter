// Fill out your copyright notice in the Description page of Project Settings.


#include "Farmer/AI/BTTask_SetNextWaypoint.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include <Farmer/FarmerBase.h>
#include "AIController.h"
#include "Farmland/FarmlandBase.h"

EBTNodeResult::Type UBTTask_SetNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	// 次のウェイポインタインデックス
	int32 NextIndex = Farmer->GetTargetWaypoint().NextIndex;

	// ウェイポイントリストを取得
	const auto& WayPoints = Farmland->GetWaypoints();

	// 次のターゲットインデックスを設定
	if (WayPoints.IsValidIndex(NextIndex))
		return EBTNodeResult::Failed;

	Farmer->SetTargetWaypoint(WayPoints[NextIndex]);

    return EBTNodeResult::Succeeded;
}

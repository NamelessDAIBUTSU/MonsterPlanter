#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Farmland/Waypoint.h"
#include "FarmerBase.generated.h"

class AFarmlandBase;

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
	// 配属先栽培場の設定
	void AssignFarmland(AFarmlandBase* Farmland);

	// 向かうウェイポイントの設定
	void SetTargetWaypoint(const FWaypoint& Waypoint) { TargetWaypoint = Waypoint; }
	const FWaypoint& GetTargetWaypoint() const { return TargetWaypoint; }

	// 配属された栽培場の取得
	AFarmlandBase* GetAssignedFarmland() const { return AssignedFarmland; }

public:
	// 周回速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Farmer Properties")
	float MoveSpeed = 400.f;

	// 育てアクションの速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Farmer Properties")	
	float FeedSpeed = 200.f;

private:
	// 向かっているウェイポイント
	UPROPERTY()
	FWaypoint TargetWaypoint;

	// 配属された栽培場
	UPROPERTY()
	TObjectPtr<AFarmlandBase> AssignedFarmland = nullptr;
};

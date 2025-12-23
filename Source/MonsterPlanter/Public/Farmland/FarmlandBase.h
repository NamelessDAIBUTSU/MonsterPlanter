#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <FarmSlot/FarmSlotBase.h>
#include "Farmland/Waypoint.h"
#include "FarmlandBase.generated.h"

class AFarmerBase;

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
	// ウェイポイントの取得
	const TArray<FWaypoint>& GetWaypoints() const { return Waypoints; }

	// 次のウェイポイントのインデックスを取得
	int GetNextWaypointIndex(int Index);

private:
	// 栽培区画の生成
	void CreateFarmSlots();
	// ウェイポイントの生成
	void CreateWaypoints();
	// 栽培員の生成
	void SpawnDefaultFarmers();

public:
	// 栽培場のメインメッシュ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> MeshComp = nullptr;

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
	float Margin = 500.f;

	// 栽培区画間のマージン
	UPROPERTY(EditAnywhere)
	float SlotWidthMargin = 300.f;
	UPROPERTY(EditAnywhere)
	float SlotHeightMargin = 200.f;

	// 生成する栽培員クラス
	UPROPERTY(EditAnywhere)
	TSubclassOf<AFarmerBase> DefaultFarmerClass;

public: /* ウェイポイント */
	// 栽培員周回用のウェイポイント配置オフセット
	UPROPERTY(EditAnywhere)
	float WaypointOffset = 250.f;

	// ウェイポイント
	UPROPERTY(EditAnywhere)
	TArray<FWaypoint> Waypoints;

protected:
	// 栽培区画リスト
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<AFarmSlotBase>> FarmSlots;

	// 栽培区画のメッシュサイズ
	FVector SlotMeshExtent = FVector::Zero();

	// 栽培員リスト
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<AFarmerBase>> Farmers;
};
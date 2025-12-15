// Fill out your copyright notice in the Description page of Project Settings.

#include "Farmland/FarmlandBase.h"
#include "Engine/World.h"
#include "Misc/OutputDeviceDebug.h"
#include "Farmer/FarmerBase.h"

AFarmlandBase::AFarmlandBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// メッシュの生成
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(RootComponent);
}

void AFarmlandBase::BeginPlay()
{
	Super::BeginPlay();

	// 栽培区画の生成
	CreateFarmSlots();

	// ウェイポイントの生成
	CreateWaypoints();

	// 栽培員の生成
	SpawnDefaultFarmers();
}

void AFarmlandBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 次のウェイポイントのインデックスを取得
int AFarmlandBase::GetNextWaypointIndex(int Index)
{
	return (Index + 1) % Waypoints.Num();
}

// 栽培区画の生成
void AFarmlandBase::CreateFarmSlots()
{
	// 前提チェック
	if (MeshComp == nullptr)
		return;

	// メッシュのバウンディングボックス取得
	FBoxSphereBounds MeshBounds = MeshComp->Bounds;
	FVector MeshOrigin = MeshBounds.Origin;
	FVector MeshExtent = MeshBounds.BoxExtent;

	// 配置開始位置（マージン分を引く）
	const float StartXPos = MeshOrigin.X + MeshExtent.X - Margin;
	const float StartYPos = MeshOrigin.Y - MeshExtent.Y + Margin;

	// 配置可能領域のサイズ
	const float AvailableWidth = MeshExtent.Y * 2.f - Margin * 2.f;
	const float AvailableHeight = MeshExtent.X * 2.f - Margin * 2.f;

	// 栽培区画の生成
	for (int i = 0; i < FarmSlotHeightNum; i++)
	{
		for (int j = 0; j < FarmSlotWidthNum; j++)
		{
			// 各区画間の距離計算
			const float DistX = i * (SlotHeightMargin + SlotMeshExtent.X * 2.f);
			const float DistY = j * (SlotWidthMargin + SlotMeshExtent.Y * 2.f);

			// 生成位置
			FVector SpawnLocation = FVector(StartXPos - DistX, StartYPos + DistY, MeshOrigin.Z + 50.f);
			FRotator SpawnRotation = i == FarmSlotHeightNum - 1 ? FRotator(0.f, 180.f, 0.f) : FRotator::ZeroRotator;
			FTransform SpawnTransform = FTransform(SpawnRotation, SpawnLocation);

			// 生成
			AFarmSlotBase* NewSlot = GetWorld()->SpawnActor<AFarmSlotBase>(FarmSlotClass, SpawnTransform);
			if (NewSlot)
			{
				FarmSlots.Add(NewSlot);

				FBoxSphereBounds SlotBounds = NewSlot->MeshComp->Bounds;
				SlotMeshExtent = SlotBounds.BoxExtent;
			}
		}
	}

	// 中央に位置調整
	{
		// 左上と右下の区間から、中心位置を計算
		FVector Dist = FarmSlots[FarmSlots.Num() - 1]->GetActorLocation() - FarmSlots[0]->GetActorLocation();
		FVector TotalCenter = FarmSlots[0]->GetActorLocation() + Dist / 2.f;

		FVector Offset = MeshOrigin - TotalCenter;
		Offset.Z = 0.f;

		// 各区画を中央に寄せる
		for (AFarmSlotBase* Slot : FarmSlots)
		{
			FVector NewPos = Slot->GetActorLocation() + Offset;
			Slot->SetActorLocation(NewPos);
		}
	}
}

// ウェイポイントの生成
void AFarmlandBase::CreateWaypoints()
{
	// 栽培区画からオフセット分離れた位置にウェイポイントを生成
	for (int i = 0;i < FarmSlots.Num();i++)
	{
		AFarmSlotBase* Slot = FarmSlots[i];
		if (Slot == nullptr)
			break;

		FWaypoint NewWaypoint;

		// 左上
		if (i == 0)
		{
			NewWaypoint.WaypointLocation = Slot->GetActorLocation() + FVector(WaypointOffset, WaypointOffset * -1.f, 0.f);
		}

		// 右上
		if (i == FarmSlotWidthNum - 1)
		{
			NewWaypoint.WaypointLocation = Slot->GetActorLocation() + FVector(WaypointOffset, WaypointOffset, 0.f);
		}

		// 左下
		if (i == FarmSlots.Num() - FarmSlotWidthNum)
		{
			NewWaypoint.WaypointLocation = Slot->GetActorLocation() + FVector(WaypointOffset * -1.f, WaypointOffset * -1.f, 0.f);
		}

		// 右下
		if (i == FarmSlots.Num() - 1)
		{
			NewWaypoint.WaypointLocation = Slot->GetActorLocation() + FVector(WaypointOffset * -1.f, WaypointOffset, 0.f);
		}
		
		if (NewWaypoint.WaypointLocation.IsNearlyZero() == false)
		{
			Waypoints.Add(NewWaypoint);
		}
	}

	// 時計回りになるようにウェイポイント同士をリンク
	for (int i = 0; i < Waypoints.Num(); i++)
	{
		// 左上 → 左下
		if (i == 0)
		{
			Waypoints[i].NextWaypoint = &Waypoints[2];
		}

		// 右上 → 左上
		if (i == 1)
		{
			Waypoints[i].NextWaypoint = &Waypoints[0];
		}

		// 左下 → 右下
		if (i == 2)
		{
			Waypoints[i].NextWaypoint = &Waypoints[3];
		}

		// 右下 → 右上
		if (i == 3)
		{
			Waypoints[i].NextWaypoint = &Waypoints[1];
		}
	}
}

// 栽培員の生成
void AFarmlandBase::SpawnDefaultFarmers()
{
	if (DefaultFarmerClass == nullptr)
		return;

	if (Waypoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnDefaultFarmers: No waypoints to spawn farmers."));
		return;
	}

	// スポーンパラメータ設定
	FActorSpawnParameters SpawnParams;
	// 衝突時のハンドリング（まずは位置調整してでもスポーンを試みる）
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	// 必要なら以下を使って強制的にスポーンできる（注意: 他アクタと重なる）
	// SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const float InitialZOffset = 50.f;
	const float RetryZIncrement = 50.f;

	for (int32 i = 0; i < Waypoints.Num(); ++i)
	{
		FVector BaseLocation = Waypoints[i].WaypointLocation;
		FVector TryLocation = BaseLocation + FVector(0.f, 0.f, InitialZOffset);
		FRotator SpawnRotation = FRotator::ZeroRotator;
		FTransform SpawnTransform(SpawnRotation, TryLocation);

		AFarmerBase* NewFarmer = GetWorld()->SpawnActor<AFarmerBase>(DefaultFarmerClass, SpawnTransform, SpawnParams);
		if (NewFarmer)
		{
			Farmers.Add(NewFarmer);

			// 配属先栽培場の設定
			NewFarmer->AssignFarmland(this);

			// ウェイポイントのZ座標を栽培員のZ座標に合わせる
			Waypoints[i].WaypointLocation.Z = NewFarmer->GetActorLocation().Z;

			// 最初の向かう先ウェイポイントインデックスを設定
			NewFarmer->SetTargetWaypoint(Waypoints[i]);

			continue;
		}

		// 1回だけ簡易リトライ（Z を上げる）
		UE_LOG(LogTemp, Warning, TEXT("SpawnDefaultFarmers: Initial spawn failed for %s at %s (index %d). Retrying with higher Z."),
			*GetNameSafe(DefaultFarmerClass), *BaseLocation.ToString(), i);

		FVector RetryLocation = BaseLocation + FVector(0.f, 0.f, InitialZOffset + RetryZIncrement);
		FTransform RetryTransform(FRotator::ZeroRotator, RetryLocation);
		NewFarmer = GetWorld()->SpawnActor<AFarmerBase>(DefaultFarmerClass, RetryTransform, SpawnParams);
		if (NewFarmer)
		{
			Farmers.Add(NewFarmer);

			// 配属先栽培場の設定
			NewFarmer->AssignFarmland(this);

			// ウェイポイントのZ座標を栽培員のZ座標に合わせる
			Waypoints[i].WaypointLocation.Z = NewFarmer->GetActorLocation().Z;

			// 最初の向かう先ウェイポイントインデックスを設定
			NewFarmer->SetTargetWaypoint(Waypoints[i]);

			return;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("SpawnDefaultFarmers: Failed to spawn farmer class %s at %s (index %d) even after retry."),
				*GetNameSafe(DefaultFarmerClass), *BaseLocation.ToString(), i);
			// 必要ならここで SpawnParams.SpawnCollisionHandlingOverride を AlwaysSpawn に変えて再試行する選択肢もある
		}
	}
}


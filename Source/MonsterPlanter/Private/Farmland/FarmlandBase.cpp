// Fill out your copyright notice in the Description page of Project Settings.

#include "Farmland/FarmlandBase.h"
#include "Engine/World.h"
#include "Misc/OutputDeviceDebug.h"

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
}

void AFarmlandBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

	// 栽培区画配置用コンポーネントの位置設定
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

			// 栽培区画の生成
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


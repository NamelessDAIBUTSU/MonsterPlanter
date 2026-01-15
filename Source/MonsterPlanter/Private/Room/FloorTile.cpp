// Fill out your copyright notice in the Description page of Project Settings.


#include "Room/Tile/FloorTile.h"
#include <Room/RoomDef.h>

AFloorTile::AFloorTile()
{
	PrimaryActorTick.bCanEverTick = true;

	// グリッド線用の親コンポーネントを作成
	GridLineRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("GridLineRootComp"));
	GridLineRootComp->SetupAttachment(RootComponent);

	// Cubeメッシュを割り当て
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(
		TEXT("/Engine/BasicShapes/Cube.Cube")
	);

	// グリッド線表示用の四辺のメッシュコンポーネントを作成
	for (int i = 0;i < 4;++i)
	{
		FName CompName = *FString::Printf(TEXT("GridLine_%d"), i);
		UStaticMeshComponent* GridLineMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(CompName);
		GridLineMeshComp->SetupAttachment(GridLineRootComp);

		GridLineMeshComps.Add(GridLineMeshComp);

		if (CubeMesh.Succeeded())
		{
			GridLineMeshComps[i]->SetStaticMesh(CubeMesh.Object);
			GridLineMeshComps[i]->SetCastShadow(false);
		}
	}
}

// BPエディタ上で確認できるように、グリッド線のメッシュコンポーネントを配置する関数をOnConstructで作成
void AFloorTile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (GridLineMeshComps.Num() != 4)
		return;
	
	// グリッド線のメッシュコンポーネントを配置
	float GridLineXYOffset = ROOM_TILE_SIZE * 0.5f + GRID_LINE_THICKNESS * 0.5f;
	float GridLineZOffset = ROOM_TILE_THICKNESS * 0.5f + GRID_LINE_THICKNESS * 0.5f;
	float GridLineScale = 0.05f;
	// 上辺
	GridLineMeshComps[0]->SetRelativeLocation(FVector(GridLineXYOffset, 0.f, GridLineZOffset));
	GridLineMeshComps[0]->SetRelativeScale3D(FVector(GridLineScale, 2.f, GridLineScale));
	// 右辺
	GridLineMeshComps[1]->SetRelativeLocation(FVector(0.f, GridLineXYOffset, GridLineZOffset));
	GridLineMeshComps[1]->SetRelativeScale3D(FVector(2.f, GridLineScale, GridLineScale));
	// 下辺
	GridLineMeshComps[2]->SetRelativeLocation(FVector(GridLineXYOffset * -1.f, 0.f, GridLineZOffset));
	GridLineMeshComps[2]->SetRelativeScale3D(FVector(GridLineScale, 2.f, GridLineScale));
	// 左辺
	GridLineMeshComps[3]->SetRelativeLocation(FVector(0.f, GridLineXYOffset * -1.f, GridLineZOffset));
	GridLineMeshComps[3]->SetRelativeScale3D(FVector(2.f, GridLineScale, GridLineScale));


}

void AFloorTile::BeginPlay()
{
	Super::BeginPlay();
}

void AFloorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// グリッド線の表示・非表示
void AFloorTile::SetGridLineVisible(bool bVisible)
{
	if (TileType == EFloorTileType::Soil)
	{
		GridLineRootComp->SetVisibility(false, true);
		return;
	}

	if (GridLineRootComp)
	{
		GridLineRootComp->SetVisibility(bVisible, true);
	}
}

bool AFloorTile::GetGridLineVisible()
{
	if (GridLineRootComp == nullptr)
		return false;

	return GridLineRootComp->GetVisibleFlag();
}

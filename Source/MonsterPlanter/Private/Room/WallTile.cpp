// Fill out your copyright notice in the Description page of Project Settings.


#include "Room/WallTile.h"

AWallTile::AWallTile()
{
	PrimaryActorTick.bCanEverTick = true;

	// メッシュコンポーネントを作成してルートコンポーネントに設定
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComp;
}

void AWallTile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWallTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


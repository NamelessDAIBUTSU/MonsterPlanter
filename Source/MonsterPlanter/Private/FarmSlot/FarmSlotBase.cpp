// Fill out your copyright notice in the Description page of Project Settings.

#include "FarmSlot/FarmSlotBase.h"

AFarmSlotBase::AFarmSlotBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// メッシュの生成（Mesh をルートコンポーネントに設定）
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComp;
}

void AFarmSlotBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFarmSlotBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


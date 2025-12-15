// Fill out your copyright notice in the Description page of Project Settings.


#include "Farmer/FarmerBase.h"
#include <Farmland/FarmlandBase.h>

AFarmerBase::AFarmerBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AFarmerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFarmerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 配属先栽培場の設定
void AFarmerBase::AssignFarmland(AFarmlandBase* Farmland)
{
	AssignedFarmland = Farmland;
}


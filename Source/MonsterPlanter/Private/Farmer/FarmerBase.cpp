// Fill out your copyright notice in the Description page of Project Settings.


#include "Farmer/FarmerBase.h"

// Sets default values
AFarmerBase::AFarmerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFarmerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFarmerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


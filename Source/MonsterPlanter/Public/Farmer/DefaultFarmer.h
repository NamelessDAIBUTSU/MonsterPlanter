// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Farmer/FarmerBase.h"
#include "DefaultFarmer.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERPLANTER_API ADefaultFarmer : public AFarmerBase
{
	GENERATED_BODY()
	
public:
	ADefaultFarmer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room/Tile/TileBase.h"
#include "FloorTile.generated.h"

UCLASS()
class MONSTERPLANTER_API AFloorTile : public ATileBase
{
	GENERATED_BODY()
	
public:	
	AFloorTile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorTile.generated.h"

UCLASS()
class MONSTERPLANTER_API AFloorTile : public AActor
{
	GENERATED_BODY()
	
public:	
	AFloorTile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	// 床タイルのメッシュコンポーネント
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshComp = nullptr;
};

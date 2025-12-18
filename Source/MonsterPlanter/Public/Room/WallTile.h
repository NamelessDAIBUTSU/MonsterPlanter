// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WallTile.generated.h"

UCLASS()
class MONSTERPLANTER_API AWallTile : public AActor
{
	GENERATED_BODY()
	
public:	
	AWallTile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	// 壁タイルのメッシュコンポーネント
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshComp = nullptr;
};

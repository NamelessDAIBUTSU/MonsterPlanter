// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick/GimmickActorBase.h"
#include "ReactionGimmickActorBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MONSTERPLANTER_API AReactionGimmickActorBase : public AGimmickActorBase
{
	GENERATED_BODY()
	
public:
	AReactionGimmickActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// ギミック起動
	virtual void ActivateGimmick() {};
};

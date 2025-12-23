// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterBase.generated.h"

UCLASS()
class MONSTERPLANTER_API AMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AMonsterBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


public:
	// モンスターデータ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
	class UMonsterData* MonsterData = nullptr;

	// スケルタルメッシュ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
	class USkeletalMeshComponent* MonsterMesh = nullptr;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GhostManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONSTERPLANTER_API UGhostManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGhostManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// ゴーストの生成

	// ゴーストの追加
	void AddGhost(class APlayerGhost* Ghost);
	TArray<TObjectPtr<class APlayerGhost>> GetGhosts() const { return Ghosts; }
	// ゴーストのクリア
	void ClearGhosts();

private:
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<class APlayerGhost>> Ghosts;

	// 現在の生成可能ゴースト数
	UPROPERTY(VisibleAnywhere)
	int32 CurrentMaxSpawnNum = 1;
};

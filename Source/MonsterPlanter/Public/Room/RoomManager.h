// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "RoomDef.h"
#include "RoomManager.generated.h"

class ARoomBase;

/**
 * 
 */
UCLASS()
class MONSTERPLANTER_API URoomManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	URoomManager();

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override {}

public:
	// 部屋の追加
	void AddRoom(ARoomBase* NewRoom);

	// 現在の部屋の取得
	ARoomBase* GetCurrentRoom() { return CurrentRoom.Get(); }

private:
	// 所持部屋リスト
	UPROPERTY()
	TSet<TObjectPtr<ARoomBase>> Rooms;

	// 現在の部屋
	UPROPERTY()
	TWeakObjectPtr<ARoomBase> CurrentRoom;
};

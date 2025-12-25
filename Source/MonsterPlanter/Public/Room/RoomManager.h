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
	// 部屋生成初期化
	void CreateDefaultRooms();

	// 部屋の生成
	void CreateRoom(ERoomType RoomType);

	// 部屋の追加
	void AddRoom(ARoomBase* NewRoom);

	// グリッド線の表示切替
	void ToggleVisibleGrid();

private:
	// 部屋クラスマップ
	UPROPERTY()
	TMap<ERoomType, TSubclassOf<ARoomBase>> RoomClassMap;

	// 所持部屋リスト
	UPROPERTY()
	TSet<TObjectPtr<ARoomBase>> Rooms;

	// 現在の部屋
	UPROPERTY()
	TObjectPtr<ARoomBase> CurrentRoom;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RoomDef.h"
#include "RoomClassInfoList.generated.h"


USTRUCT(BlueprintType)
struct FRoomClassInfo
{
	GENERATED_BODY()

public:
	// 部屋クラスが持っているが、生成前の検索用
	UPROPERTY(EditAnywhere)
	ERoomType RoomType;

	// 部屋クラス
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARoomBase> RoomClass;
};

/**
 * 
 */
UCLASS()
class MONSTERPLANTER_API URoomClassInfoList : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// 部屋クラスリスト
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRoomClassInfo> RoomClassInfoList;
};

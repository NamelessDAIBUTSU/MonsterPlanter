// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room/RoomDef.h"
#include "TileBase.generated.h"

UCLASS()
class MONSTERPLANTER_API ATileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ATileBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	// マテリアルの設定
	void SetTileMaterial(UMaterialInterface* Material);

public:
	// タイルタイプ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFloorTileType TileType;

private:
	// 壁タイルのメッシュコンポーネント
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComp = nullptr;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/IngameCameraBase.h"
#include "GodCameraActor.generated.h"

/**
 * 神視点カメラ（上から見下ろすカメラ）
 * PlayerController から PanCamera / ZoomCamera / RotateCamera を呼んで操作します。
 */
UCLASS()
class MONSTERPLANTER_API AGodCameraActor : public AIngameCameraBase
{
	GENERATED_BODY()

public:
	AGodCameraActor();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position")
	float BaseHeight = 800.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position")
	float HeightOffset = 20.f;
};
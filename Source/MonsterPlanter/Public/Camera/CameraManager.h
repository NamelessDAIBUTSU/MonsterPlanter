// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CameraDef.h"
#include "CameraManager.generated.h"

class AIngameCameraBase;

/**
 * 
 */
UCLASS()
class MONSTERPLANTER_API UCameraManager : public UObject
{
	GENERATED_BODY()
	
public:
	UCameraManager();

public:
	void Initialize();
	
	// カメラの登録
	void RegisterCamera(AIngameCameraBase* NewCamera);
	// カメラの登録解除
	void UnregisterCamera(AIngameCameraBase* RemoveCamera);

	// カメラの取得
	AIngameCameraBase* GetCamera(ECameraChannel Cannel);

	// 現在のカメラを取得
	AIngameCameraBase* GetCurrentCamera() const;
	// 現在のカメラを設定
	void SetCurrentCamera(AIngameCameraBase* NewCamera);

	// 登録されたカメラのリストを取得
	const TArray<AIngameCameraBase*>& GetCameraList() const;


private:
	// 現在のカメラ
	TObjectPtr<AIngameCameraBase> CurrentCamera;

	// 登録されたカメラのリスト
	TArray<TObjectPtr<AIngameCameraBase>> CameraList;
};

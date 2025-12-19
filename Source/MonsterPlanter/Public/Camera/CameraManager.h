// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CameraDef.h"
#include "CameraManager.generated.h"

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
	void RegisterCamera(class AIngameCameraBase* NewCamera);
	// カメラの登録解除
	void UnregisterCamera(class AIngameCameraBase* RemoveCamera);

	// カメラの取得
	class AIngameCameraBase* GetCamera(ECameraChannel Cannel);

	// 現在のカメラを取得
	class AIngameCameraBase* GetCurrentCamera() const;
	// 現在のカメラを設定
	void SetCurrentCamera(class AIngameCameraBase* NewCamera);

	// 登録されたカメラのリストを取得
	const TArray<class AIngameCameraBase*>& GetCameraList() const;


private:
	// 現在のカメラ
	class AIngameCameraBase* CurrentCamera;

	// 登録されたカメラのリスト
	TArray<class AIngameCameraBase*> CameraList;
};

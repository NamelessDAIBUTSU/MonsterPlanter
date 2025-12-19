#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraDef.h"
#include "GodPlayerController.generated.h"

UCLASS()
class MONSTERPLANTER_API AGodPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGodPlayerController();

protected:
	virtual void BeginPlay() override;

	// 入力バインド設定
	virtual void SetupInputComponent() override;

	
public:
	// カメラマネージャーの取得
	class UCameraManager* GetCameraManager() const { return CameraManager; }

	// カメラを神カメラに切り替え
	UFUNCTION()
	void SwitchToGodCamera();
	// カメラを部屋カメラに切り替え
	UFUNCTION()
	void SwitchToRoomCamera();

private:
	// カメラ切り替え
	void SwitchCamera();

public:
	// 入力処理関連
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* IMC = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* IAGodCamera = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* IARoomCamera = nullptr;

private:
	// カメラマネージャー
	UPROPERTY()
	class UCameraManager* CameraManager = nullptr;

	// 現在のカメラチャンネル
	ECameraChannel CurrentCameraChannel = ECameraChannel::God;
};
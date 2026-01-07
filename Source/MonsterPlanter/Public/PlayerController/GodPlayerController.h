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
	// カメラを神カメラに切り替え
	UFUNCTION()
	void SwitchToGodCamera();
	// カメラを部屋カメラに切り替え
	UFUNCTION()
	void SwitchToRoomCamera();
	// グリッド線の表示切替
	UFUNCTION()
	void ToggleVisibleGridLine();

private:
	// カメラ切り替え
	void SwitchCamera();

public:
	// 入力処理関連
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> IMC;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IAGodCamera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IARoomCamera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IAToggleVisibleGrid;

private:
	// 現在のカメラチャンネル
	ECameraChannel CurrentCameraChannel = ECameraChannel::God;
};
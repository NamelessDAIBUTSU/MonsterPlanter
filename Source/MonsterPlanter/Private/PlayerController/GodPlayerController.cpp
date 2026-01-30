#include "PlayerController/GodPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/GodCameraActor.h"
#include <Camera/CameraManager.h>
#include <Room/RoomManager.h>
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>

AGodPlayerController::AGodPlayerController()
{

}

void AGodPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// マウス可視化とクリックイベントを有効にする
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	// 入力マッピングコンテキスト登録
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC, 0);
	}

	// カメラ生成
	UCameraManager* CameraManager = GetWorld()->GetSubsystem<UCameraManager>();
	if (CameraManager)
	{
		if (AGodCameraActor* Camera = GetWorld()->SpawnActor<AGodCameraActor>())
		{
			// プレイヤーのビューをこのカメラに固定
			SetViewTargetWithBlend(Camera, 0.0f);

			// カメラマネージャーに登録
			CameraManager->RegisterCamera(Camera);
		}
	}
}

// 入力バインド設定
void AGodPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// カメラ切り替え
		EIC->BindAction(IAGodCamera, ETriggerEvent::Started, this, &AGodPlayerController::SwitchToGodCamera);
		EIC->BindAction(IARoomCamera, ETriggerEvent::Started, this, &AGodPlayerController::SwitchToRoomCamera);
	}
}

// カメラを神カメラに切り替え
void AGodPlayerController::SwitchToGodCamera()
{
	CurrentCameraChannel = ECameraChannel::God;
	SwitchCamera();
}
// カメラを部屋カメラに切り替え
void AGodPlayerController::SwitchToRoomCamera()
{
	CurrentCameraChannel = ECameraChannel::Room1;
	SwitchCamera();
}

// カメラ切り替え
void AGodPlayerController::SwitchCamera()
{
	if (UCameraManager* CameraManager = GetWorld()->GetSubsystem<UCameraManager>())
	{
		// 該当カメラの取得
		AIngameCameraBase* NextCamera = CameraManager->GetCamera(CurrentCameraChannel);

		if (NextCamera)
		{
			// プレイヤーのビューをこのカメラに固定
			SetViewTargetWithBlend(NextCamera, 0.f);

			// 現在のカメラを設定
			CameraManager->SetCurrentCamera(NextCamera);
		}
	}
}


#include "PlayerController/GodPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/GodCameraActor.h"

void AGodPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// マウス可視化とクリックイベントを有効にする
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	// 必要ならここで既存の CameraActor を SetViewTarget() する
	// 例: AActor* Cam = UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass());
	// if (Cam) { SetViewTarget(Cam); }

		// カメラ生成
	if (AGodCameraActor* Camera = GetWorld()->SpawnActor<AGodCameraActor>())
	{
		// プレイヤーのビューをこのカメラに固定
		SetViewTargetWithBlend(Camera, 0.0f);
	}
}



#include "PlayerController/MyPlayerController.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <Player/PlayerBody.h>

AMyPlayerController::AMyPlayerController()
{
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 入力マッピングコンテキスト登録
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC, 0);
	}

	if (APawn* P = GetPawn())
	{
		UE_LOG(LogTemp, Warning, TEXT("Pawn spawned at: %s"), *P->GetActorLocation().ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Pawn on BeginPlay"));
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

}



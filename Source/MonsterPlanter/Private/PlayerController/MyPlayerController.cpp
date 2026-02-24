
#include "PlayerController/MyPlayerController.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <Player/Body/PlayerBody.h>
#include <Player/Astral/PlayerAstral.h>
#include <Player/Ghost/PlayerGhost.h>
#include "Player/Ghost/GhostManagerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyPlayerController::AMyPlayerController()
{
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 最初は本体用コンテキストを登録
	ActivateBodyInputContext();
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// 関数のバインド
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);
		EIC->BindAction(IA_Mouse, ETriggerEvent::Triggered, this, &AMyPlayerController::RotateCamera);
		EIC->BindAction(IA_Astral, ETriggerEvent::Started, this, &AMyPlayerController::ChangeToAstralMode);
		EIC->BindAction(IA_Body, ETriggerEvent::Started, this, &AMyPlayerController::ChangeToBodyMode);
		EIC->BindAction(IA_Ghost, ETriggerEvent::Started, this, &AMyPlayerController::SpawnGhost);
		EIC->BindAction(IA_Dodge, ETriggerEvent::Started, this, &AMyPlayerController::Dodge);
	}
}

void AMyPlayerController::ActivateBodyInputContext()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(IMC_Body, 0);
	}
}

void AMyPlayerController::ActivateAstralInputContext()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(IMC_Astral, 0);
	}
}

// アストラルモードに変更
void AMyPlayerController::ChangeToAstralMode()
{
	// 本体の取得
	APlayerBody* Body =  Cast<APlayerBody>(GetPawn());
	if (Body == nullptr)
		return;

	UGhostManagerComponent* GhostManComp = Body->GetGhostManagerComponent();
	if (GhostManComp == nullptr)
		return;

	// ゴーストの全削除
	GhostManComp->ClearGhosts();

	// アストラルの生成
	APlayerAstral* Astral = GetWorld()->SpawnActor<APlayerAstral>(AstralClass, Body->GetActorLocation(), Body->GetActorRotation());
	if (Astral == nullptr)
		return;

	// 本体の登録
	Astral->SetBody(Body);

	// コントローラーをアストラルにPossess
	Possess(Astral);

	// アストラル用IMCをアクティブ化
	ActivateAstralInputContext();

	// 本体のアニメーションを止めるために移動を測定し
	if (UCharacterMovementComponent* MoveComp = Body->GetCharacterMovement())
	{
		MoveComp->StopMovementImmediately();
	}
}

// 本体モードに変更
void AMyPlayerController::ChangeToBodyMode()
{
	// アストラルの取得
	APlayerAstral* Astral = Cast<APlayerAstral>(GetPawn());
	if (Astral == nullptr)
		return;

	// コントローラーをBodyにPossess
	Possess(Astral->GetBody());

	// アストラルを消す
	Astral->Destroy();

	// 本体用IMCをアクティブ化
	ActivateBodyInputContext();
}

// ゴーストの生成
void AMyPlayerController::SpawnGhost()
{
	// 本体の取得
	APlayerBody* Body = Cast<APlayerBody>(GetPawn());
	if (Body == nullptr)
		return;
	UGhostManagerComponent* GhostManComp = Body->GetGhostManagerComponent();
	if (GhostManComp == nullptr)
		return;

	// ゴーストの全削除
	GhostManComp->ClearGhosts();

	// 軌道の数だけゴーストを生成
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	for (const TArray<FAstralOrbitData>& Orbit : Body->GetOrbitDatas())
	{
		if (Orbit.IsEmpty())
			continue;

		// ゴーストの生成
		APlayerGhost* Ghost = GetWorld()->SpawnActor<APlayerGhost>(GhostClass, Orbit[0].TargetTransform.GetLocation(), Orbit[0].TargetTransform.GetRotation().Rotator(), Params);
		if (Ghost == nullptr)
			return;

		// 軌道の登録
		Ghost->SetOrbitPoints(Orbit);

		// 本体の登録
		Ghost->SetBody(Body);

		// ゴーストの登録
		GhostManComp->AddGhost(Ghost);
	}
}

void AMyPlayerController::Move(const FInputActionValue& Value)
{
	// Possessしているキャラクターを取得
	ACharacter* PossessCharacter = Cast<ACharacter>(GetPawn());
	if (PossessCharacter == nullptr)
		return;

	const FVector2D InputAxis = Value.Get<FVector2D>();

	// カメラ軸で移動
	// カメラの取得
	FRotator CameraRot = GetControlRotation();
	// カメラの回転から前方向と右方向を計算
	FRotationMatrix CameraRotMat(CameraRot);
	FVector Forward = CameraRotMat.GetUnitAxis(EAxis::X);
	FVector Right = CameraRotMat.GetUnitAxis(EAxis::Y);

	PossessCharacter->AddMovementInput(Forward, InputAxis.X);
	PossessCharacter->AddMovementInput(Right, InputAxis.Y);
}

// カメラ回転
void AMyPlayerController::RotateCamera(const FInputActionValue& Value)
{
	const FVector2D InputAxis = Value.Get<FVector2D>();
	if (InputAxis.IsZero())
		return;

	APlayerBody* Body = Cast<APlayerBody>(GetPawn());
	if (Body == nullptr)
		return;

	Body->RotateCamera(InputAxis);

	// ログ
	UE_LOG(LogTemp, Log, TEXT("Camera Rotated: %s"), *InputAxis.ToString());
}

void AMyPlayerController::Dodge()
{
	// 本体の取得
	APlayerBody* Body = Cast<APlayerBody>(GetPawn());
	if (Body == nullptr)
		return;

	if (Body->IsPlayingDodge())
		return;

	// 回避行動
	Body->Dodge();
}

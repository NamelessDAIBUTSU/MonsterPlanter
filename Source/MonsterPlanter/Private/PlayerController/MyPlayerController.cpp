
#include "PlayerController/MyPlayerController.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <Player/PlayerBody.h>
#include <Player/PlayerAstral.h>
#include <Player/PlayerGhost.h>

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
		EIC->BindAction(IA_Astral, ETriggerEvent::Started, this, &AMyPlayerController::ChangeToAstralMode);
		EIC->BindAction(IA_Body, ETriggerEvent::Started, this, &AMyPlayerController::ChangeToBodyMode);
		EIC->BindAction(IA_Ghost, ETriggerEvent::Started, this, &AMyPlayerController::SpawnGhost);
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

	// 軌道の数だけゴーストを生成
	for (TArray<FTransform> Orbit : Body->GetOrbitPoints())
	{
		if (Orbit.IsEmpty())
			continue;

		// ゴーストの生成
		APlayerGhost* Ghost = GetWorld()->SpawnActor<APlayerGhost>(GhostClass, Orbit[0].GetLocation(), Orbit[0].GetRotation().Rotator());
		if (Ghost == nullptr)
			return;

		// 軌道の登録
		Ghost->SetOrbitPoints(Orbit);

		// 本体の登録
		Ghost->SetBody(Body);
	}
}

void AMyPlayerController::Move(const FInputActionValue& Value)
{
	// Possessしているキャラクターを取得
	ACharacter* PossessCharacter = Cast<ACharacter>(GetPawn());
	if (PossessCharacter == nullptr)
		return;

	const FVector2D InputAxis = Value.Get<FVector2D>();
	PossessCharacter->AddMovementInput(FVector::ForwardVector, InputAxis.X);
	PossessCharacter->AddMovementInput(FVector::RightVector, InputAxis.Y);
}
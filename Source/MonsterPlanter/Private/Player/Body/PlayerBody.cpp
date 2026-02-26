// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Body/PlayerBody.h"
#include "Player/Ghost/PlayerGhost.h"
#include <Player/Astral/PlayerAstral.h>
#include <EnhancedInputComponent.h>
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/Ghost/GhostManagerComponent.h"
#include "ActorComponent/DodgeComponent.h"
#include "ActorComponent/CombatComponent.h"
#include "ActorComponent/HealthComponent.h"
#include "ActorComponent/VoltageComponent.h"
#include <Voltage/VoltageManager.h>

// Sets default values
APlayerBody::APlayerBody()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	// Create a camera...
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	// コンポーネントの作成
	DodgeComp = CreateDefaultSubobject<UDodgeComponent>(TEXT("Dodge"));
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat"));
	HPComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	VoltageComp = CreateDefaultSubobject<UVoltageComponent>(TEXT("Voltage"));

	GhostManagerComp = CreateDefaultSubobject<UGhostManagerComponent>(TEXT("GhostManager"));
}

// Called when the game starts or when spawned
void APlayerBody::BeginPlay()
{
	Super::BeginPlay();

	// イベントのバインド

	// ジャスト回避
	if (UVoltageManager* VoltageManager = GetWorld()->GetSubsystem<UVoltageManager>())
	{
		if (DodgeComp)
		{
			DodgeComp->OnJustDodgeDelegate.AddUObject(VoltageManager, &UVoltageManager::ApplyJustDodge);
		}
	}

	// 攻撃受信
	if (CombatComp)
	{
	}
}

// Called every frame
void APlayerBody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerBody::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// 攻撃を受信
EAttackResult APlayerBody::ReceiveAttack(const FAttackData& AttackData)
{
	// 戦闘はCombatComponentに任せる
	if (CombatComp)
	{
		return CombatComp->ReceiveAttack(AttackData);
	}

	return EAttackResult::None;
}

// 軌道の保存
void APlayerBody::SetOrbitData(const TArray<FAstralOrbitData>& Data)
{
	OrbitDatas.Add(Data);
}

// 落下用のカメラ回転に切り替え
void APlayerBody::ChangeToFallCameraRotate()
{
	if (SpringArmComp == nullptr)
		return;

	//SpringArmComp->TargetArmLength = FallCameraArmLength;
	//SpringArmComp->SetRelativeRotation(FallCameraRotation);
}

// 通常用のカメラ回転に切り替え
void APlayerBody::ChangeToNormalCameraRotate()
{
	if (SpringArmComp == nullptr)
		return;

	//SpringArmComp->TargetArmLength = NormalCameraArmLength;
	//SpringArmComp->SetRelativeRotation(NormalCameraRotation);
}

void APlayerBody::RotateCamera(FVector2D RotateVec)
{
	if (IsValid(SpringArmComp) == false)
		return;

	if (RotateVec.X != 0.f)
	{
		float XRotateSpeed = RotateVec.X < 0.f ? CameraXRotateSpeed * -1.f : CameraXRotateSpeed;
		AddControllerYawInput(XRotateSpeed);
	}
	if (RotateVec.Y != 0.f)
	{
		float YRotateSpeed = RotateVec.Y < 0.f ? CameraYRotateSpeed * -1.f : CameraYRotateSpeed;
		AddControllerPitchInput(YRotateSpeed);
	}
}

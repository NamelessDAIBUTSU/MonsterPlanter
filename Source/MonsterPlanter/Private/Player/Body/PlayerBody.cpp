// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Body/PlayerBody.h"
#include "Player/Ghost/PlayerGhost.h"
#include <Player/Astral/PlayerAstral.h>
#include <EnhancedInputComponent.h>
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/Ghost/GhostManagerComponent.h"

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
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->SetUsingAbsoluteRotation(true);
	SpringArmComp->bDoCollisionTest = false;
	ChangeToNormalCameraRotate();

	// Create a camera...
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	GhostManagerComp = CreateDefaultSubobject<UGhostManagerComponent>(TEXT("GhostManager"));
}

// Called when the game starts or when spawned
void APlayerBody::BeginPlay()
{
	Super::BeginPlay();
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

	SpringArmComp->TargetArmLength = FallCameraArmLength;
	SpringArmComp->SetRelativeRotation(FallCameraRotation);
}

// 通常用のカメラ回転に切り替え
void APlayerBody::ChangeToNormalCameraRotate()
{
	if (SpringArmComp == nullptr)
		return;

	SpringArmComp->TargetArmLength = NormalCameraArmLength;
	SpringArmComp->SetRelativeRotation(NormalCameraRotation);
}

// 回避行動
void APlayerBody::Dodge()
{
	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		if (MoveComp->IsFalling())
			return;
	}

	if (UAnimInstance* AnimInst = GetMesh()->GetAnimInstance())
	{
		if (IsValid(DodgeMontage))
		{
			AnimInst->Montage_Play(DodgeMontage);
		}
	}
}

bool APlayerBody::IsPlayingDodge()
{
	if (UAnimInstance* AnimInst = GetMesh()->GetAnimInstance())
	{
		return AnimInst->Montage_IsPlaying(DodgeMontage);
	}

	return false;
}

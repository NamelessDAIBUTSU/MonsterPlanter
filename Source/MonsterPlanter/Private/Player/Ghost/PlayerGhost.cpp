// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Ghost/PlayerGhost.h"
#include "Player/Body/PlayerBody.h"
#include <EnhancedInputComponent.h>
#include "GameFramework/PawnMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerGhost::APlayerGhost()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

// Called when the game starts or when spawned
void APlayerGhost::BeginPlay()
{
	Super::BeginPlay();
	

}

void APlayerGhost::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);


}

// Called every frame
void APlayerGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 移動更新
	UpdateMove(DeltaTime);
}

// Called to bind functionality to input
void APlayerGhost::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}

// 幽体離脱した本体の設定
void APlayerGhost::SetBody(APlayerBody* Body)
{
	PlayerBody = Body;
}

APlayerBody* APlayerGhost::GetBody()
{
	return PlayerBody.Get();
}

void APlayerGhost::OnTimerDestroy()
{
	Destroy();
}


// 移動更新
void APlayerGhost::UpdateMove(float DeltaTime)
{
	if (bIsMoveFinished)
		return;

	if (OrbitPoints.IsEmpty() || OrbitPoints.IsValidIndex(CurrentOrbitIndex) == false)
	{
		bIsMoveFinished = true;

		// 移動完了したら、時間計測して一定時間経過後に消滅させる
		GetWorldTimerManager().SetTimer(
			DestroyTimerHandle,
			this,
			&APlayerGhost::OnTimerDestroy,
			DeleteSec,
			false
		);

		return;
	}


	// 現在の目標地点
	const FTransform& TargetTransform = OrbitPoints[CurrentOrbitIndex];
	const FVector TargetLocation = TargetTransform.GetLocation();

	// 現在位置
	const FVector CurrentLocation = GetActorLocation();

	// 目標方向
	FVector ToTarget = TargetTransform.GetLocation() - CurrentLocation;
	const float DistanceToTarget = ToTarget.Size();
	ToTarget.Normalize();

	// 本体の移動速度を取得
	APlayerBody* Body = GetBody();
	if (Body == nullptr || Body->GetMovementComponent() == nullptr)
		return;

	const float MoveSpeed = Body->GetMovementComponent()->GetMaxSpeed();

	// 移動量
	const FVector MoveDelta = ToTarget * MoveSpeed * DeltaTime;

	// 目標に到達したか
	if (DistanceToTarget <= MoveDelta.Size())
	{
		// 到達したら位置補正して次の目標へ
		SetActorLocation(TargetLocation);
		SetActorRotation(MoveDelta.Rotation());
		CurrentOrbitIndex++;;
	}
	else
	{
		// 到達していなければ移動
		SetActorLocation(CurrentLocation + MoveDelta);
		SetActorRotation(MoveDelta.Rotation());
	}
}

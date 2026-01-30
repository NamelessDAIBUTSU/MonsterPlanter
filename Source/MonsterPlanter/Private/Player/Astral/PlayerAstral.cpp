// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Astral/PlayerAstral.h"
#include "Player/Body/PlayerBody.h"
#include <EnhancedInputComponent.h>
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerAstral::APlayerAstral()
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
void APlayerAstral::BeginPlay()
{
	Super::BeginPlay();
	
}

// Destroy時に軌道を本体に渡す
void APlayerAstral::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (PlayerBody.IsValid())
	{
		PlayerBody->SetOrbitPoints(OrbitPoints);
	}
}

// Called every frame
void APlayerAstral::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedSec += DeltaTime;

	// 軌道保存
	if (ElapsedSec >= OrbitSaveInterval)
	{
		OrbitPoints.Add(GetActorTransform());
		
		ElapsedSec = 0.f;
	}
}

// Called to bind functionality to input
void APlayerAstral::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// 幽体離脱した本体の設定
void APlayerAstral::SetBody(APlayerBody* Body) 
{
	PlayerBody = Body; 
}

APlayerBody* APlayerAstral::GetBody() 
{
	return PlayerBody.Get(); 
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerBody.h"
#include "Player/PlayerGhost.h"
#include <Player/PlayerAstral.h>
#include <EnhancedInputComponent.h>
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Ghost/GhostManagerComponent.h"

// Sets default values
APlayerBody::APlayerBody()
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
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	SpringArmComp->TargetArmLength = 800.f;
	SpringArmComp->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArmComp->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	GhostManagerComp = CreateDefaultSubobject<UGhostManagerComponent>(TEXT("GhostManager"));

	UE_LOG(LogTemp, Warning, TEXT("APlayerBody::APlayerBody() Pawn spawned at: %s"), *GetActorLocation().ToString());
}

// Called when the game starts or when spawned
void APlayerBody::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("APlayerBody::BeginPlay() Pawn spawned at: %s"), *GetActorLocation().ToString());
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
void APlayerBody::SetOrbitPoints(const TArray<FTransform>& Points)
{
	OrbitPoints.Add(Points);
}


// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/GodCameraActor.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include <Kismet/GameplayStatics.h>
#include <GameMode/IngameGameMode.h>

AGodCameraActor::AGodCameraActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraChannel = ECameraChannel::God;
}

void AGodCameraActor::BeginPlay()
{
	Super::BeginPlay();

	if (AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this))
	{
		if (AIngameGameMode* IngameGM = Cast<AIngameGameMode>(GameMode))
		{
			SetActorLocation(FVector(-750.f, 0.f, 1100.f));
			SetActorRotation(FRotator(-60.f, 0.f, 0.f));
		}
	}
}

void AGodCameraActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

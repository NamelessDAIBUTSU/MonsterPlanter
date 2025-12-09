// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/GodCameraActor.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include <Kismet/GameplayStatics.h>
#include <GameMode/IngameGameMode.h>

AGodCameraActor::AGodCameraActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGodCameraActor::BeginPlay()
{
	Super::BeginPlay();

	if (AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this))
	{
		if (AIngameGameMode* IngameGM = Cast<AIngameGameMode>(GameMode))
		{
			SetActorLocation(FVector(-500.f, 1750.f, 1800.f));
			SetActorRotation(FRotator(-50.f, 0.f, 0.f));
		}
	}
}

void AGodCameraActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

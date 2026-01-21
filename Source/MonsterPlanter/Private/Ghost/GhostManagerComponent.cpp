// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost/GhostManagerComponent.h"
#include "Player/PlayerGhost.h"

// Sets default values for this component's properties
UGhostManagerComponent::UGhostManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGhostManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGhostManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGhostManagerComponent::AddGhost(APlayerGhost* Ghost)
{
	Ghosts.Add(Ghost);
}

// 全ゴーストをクリア
void UGhostManagerComponent::ClearGhosts()
{
	// ワールドから削除
	for (APlayerGhost* Ghost : Ghosts)
	{
		Ghost->Destroy();
	}

	// リストから削除
	Ghosts.Empty();
}

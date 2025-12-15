// Fill out your copyright notice in the Description page of Project Settings.


#include "Farmer/AI/FarmerAIController.h"

AFarmerAIController::AFarmerAIController()
{
}

void AFarmerAIController::BeginPlay()
{
    Super::BeginPlay();

    if (BehaviorTreeAsset)
    {
        RunBehaviorTree(BehaviorTreeAsset);
    }
}
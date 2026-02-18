// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AnimNotify/AnimNotify_SetInvincible.h"
#include "Player/Body/PlayerBody.h"

void UAnimNotify_SetInvincible::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// プレイヤーを無敵状態にする
	if (APlayerBody* PlayerBody = Cast<APlayerBody>(MeshComp->GetOwner()))
	{
		PlayerBody->StartInvincible();
	}
}

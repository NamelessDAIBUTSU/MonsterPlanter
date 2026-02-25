// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DodgeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONSTERPLANTER_API UDodgeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDodgeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// 回避行動
	void Dodge();

	// 回避中か
	bool IsPlayingDodge();

	// 無敵状態の開始
	void StartInvincible();

	// 無敵時間終了時刻の取得
	float GetInvincibleEndTime() const;

private:
	// 回避アニメーションモンタージュ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DodgeMontage;

	// 無敵時間
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float InvincibleDuration = 0.15f;

	// 無敵状態終了時間
	float InvincibleEndTime = 0.f;
};

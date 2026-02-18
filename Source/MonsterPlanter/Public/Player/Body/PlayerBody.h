// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interface/Weighted.h"
#include <Player/PlayerDef.h>
#include "PlayerBody.generated.h"

class APlayerGhost;
class UGhostManagerComponent;

UCLASS()
class MONSTERPLANTER_API APlayerBody : public ACharacter, public IWeighted
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerBody();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: /* IWeighted */
	virtual float GetWeight() const override { return 1.0f; }

public:
	// ゴースト管理コンポーネントの取得
	UGhostManagerComponent* GetGhostManagerComponent() const { return GhostManagerComp; }

	// 軌道の保存
	void SetOrbitData(const TArray<FAstralOrbitData>& Data);
	TArray<TArray<FAstralOrbitData>> GetOrbitDatas() const { return OrbitDatas; }

	// 落下用のカメラ回転に切り替え
	void ChangeToFallCameraRotate();
	// 通常用のカメラ回転に切り替え
	void ChangeToNormalCameraRotate();

	// 回避行動
	void Dodge();
	bool IsPlayingDodge();

	// 無敵状態の開始
	void StartInvincible();

	// 無敵時間終了時刻の取得
	float GetInvincibleEndTime() const { return InvincibleEndTime; }

public:
	// 通常カメラ
	UPROPERTY(EditAnywhere)
	FRotator NormalCameraRotation = FRotator(-45.f, 0.f, 0.f);
	UPROPERTY(EditAnywhere)
	float NormalCameraArmLength = 1000.f;

	UPROPERTY(EditAnywhere)
	FRotator FallCameraRotation = FRotator(-20.f, 0.f, 0.f);
	UPROPERTY(EditAnywhere)
	float FallCameraArmLength = 500.f;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> CameraComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGhostManagerComponent> GhostManagerComp;

	// 保存した軌道
	TArray<TArray<FAstralOrbitData>> OrbitDatas;

private:
	// 無敵時間
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float InvincibleDuration = 0.15f;

	// 無敵状態終了時間
	float InvincibleEndTime = 0.f;

private: /* アニメーション */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DodgeMontage;
};

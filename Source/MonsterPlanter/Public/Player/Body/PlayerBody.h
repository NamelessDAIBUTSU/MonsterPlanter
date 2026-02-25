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

	// カメラ回転
	void RotateCamera(FVector2D RotateVec);

public: /* カメラ */
	// マウスによるカメラ回転スピード
	UPROPERTY(EditAnywhere)
	float CameraXRotateSpeed = 0.1f;
	UPROPERTY(EditAnywhere)
	float CameraYRotateSpeed = 0.1f;

private: /* コンポーネント */
	// カメラコンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> CameraComp;

	// カメラ回転用のスプリングアームコンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArmComp;

	// 回避コンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UDodgeComponent> DodgeComp;

	// 戦闘コンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCombatComponent> CombatComp;

	// HP管理コンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UHealthComponent> HPComp;

	// ボルテージコンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UVoltageComponent> VoltageComp;

	// 保存した軌道
	TArray<TArray<FAstralOrbitData>> OrbitDatas;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGhostManagerComponent> GhostManagerComp;

};

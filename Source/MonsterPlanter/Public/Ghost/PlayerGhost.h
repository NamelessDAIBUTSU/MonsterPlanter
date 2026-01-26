// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/Weighted.h"
#include "PlayerGhost.generated.h"

class APlayerBody;

UCLASS()
class MONSTERPLANTER_API APlayerGhost : public ACharacter, public IWeighted
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerGhost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: /* IWeighted */
	virtual float GetWeight() const override { return 1.0f; }

public:
	// 幽体離脱した本体の設定
	void SetBody(APlayerBody* Body);
	APlayerBody* GetBody();

	void SetOrbitPoints(const TArray<FTransform>& Points) { OrbitPoints = Points; }

	UFUNCTION()
	void OnTimerDestroy();

private:
	// 移動更新
	void UpdateMove(float DeltaTime);

private:
	// 本体への参照
	TWeakObjectPtr<APlayerBody> PlayerBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// 移動予定軌跡
	TArray<FTransform> OrbitPoints;
	// 現在の軌跡インデックス
	int32 CurrentOrbitIndex = 0;

	// 最終地点に到達したか
	bool bIsMoveFinished = false;

	// ゴースト削除までの経過時間
	UPROPERTY(EditAnywhere)
	float DeleteSec = 3.f;

	FTimerHandle DestroyTimerHandle;
};

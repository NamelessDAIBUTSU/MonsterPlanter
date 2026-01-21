// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerGhost.generated.h"

class APlayerBody;

UCLASS()
class MONSTERPLANTER_API APlayerGhost : public ACharacter
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

public:
	// 幽体離脱した本体の設定
	void SetBody(APlayerBody* Body);
	APlayerBody* GetBody();

	void SetOrbitPoints(const TArray<FTransform>& Points) { OrbitPoints = Points; }

private:
	// 移動更新
	void UpdateMove(float DeltaTime);

private:
	// 本体への参照
	TWeakObjectPtr<APlayerBody> PlayerBody;

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// 移動予定軌跡
	TArray<FTransform> OrbitPoints;
	// 現在の軌跡インデックス
	int32 CurrentOrbitIndex = 0;
};

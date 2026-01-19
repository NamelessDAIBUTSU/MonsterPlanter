// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerAstral.generated.h"

class APlayerBody;

UCLASS()
class MONSTERPLANTER_API APlayerAstral : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerAstral();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// 幽体離脱した本体の設定
	void SetBody(APlayerBody* Body);
	APlayerBody* GetBody();

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

private:
	// 本体への参照
	TWeakObjectPtr<APlayerBody> PlayerBody;

	// 軌道保存
	TArray<FTransform> OrbitPoints;

	// 軌道保存間隔(s)
	float OrbitSaveInterval = 0.05f;

	// 経過時間
	float ElapsedSec = 0.f;
};

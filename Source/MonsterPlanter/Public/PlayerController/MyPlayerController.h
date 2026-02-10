// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERPLANTER_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

protected:
	virtual void BeginPlay() override;
	// 入力バインド設定
	virtual void SetupInputComponent() override;

public:
	// 移動
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	// 避ける
	UFUNCTION()
	void Dodge();

	// アストラルモードに変更
	UFUNCTION()
	void ChangeToAstralMode();
	// 本体モードに変更
	UFUNCTION()
	void ChangeToBodyMode();
	// ゴーストの生成
	UFUNCTION()
	void SpawnGhost();

private:
	// 本体用入力コンテキストをアクティブにする
	void ActivateBodyInputContext();

	// アストラル用入力コンテキストをアクティブにする
	void ActivateAstralInputContext();

public:
	// 本体用入力コンテキスト
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> IMC_Body;
	// アストラル用入力コンテキスト
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> IMC_Astral;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IA_Move;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IA_Astral;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IA_Ghost;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IA_Body;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IA_Dodge;

	// 生成するゴーストクラス
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<APawn> GhostClass;
	// 生成するアストラルクラス
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<APawn> AstralClass;
};

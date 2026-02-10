// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "VoltageDef.h"
#include "VoltageManager.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERPLANTER_API UVoltageManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UVoltageManager();

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override {}
	virtual void Deinitialize() override {}

public:
	// ボルテージ値 → ボルテージランク変換処理
	EVoltageRank ConvertVoltageToRank(float Voltage);

	// 現在のボルテージ値
	float GetCurrentVoltage() const { return CurrentVoltage; }
	void SetCurrentVoltage(float Voltage) { CurrentVoltage = Voltage; }
	void AddVoltage(float Voltage) { CurrentVoltage += Voltage; }
	void SubtractVoltage(float Voltage) { CurrentVoltage -= Voltage; }

	// 現在のボルテージランクを取得
	EVoltageRank GetCurrentVoltageRank() const { return CurrentRank; }
	void SetCurrentVoltageRank(EVoltageRank Rank) { CurrentRank = Rank; }

private:
	// 現在のボルテージ値
	float CurrentVoltage = 0.f;

	// 現在のボルテージランク
	EVoltageRank CurrentRank = EVoltageRank::Rank0;
};

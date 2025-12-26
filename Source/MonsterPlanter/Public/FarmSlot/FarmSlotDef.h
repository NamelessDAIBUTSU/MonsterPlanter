// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// 栽培区画のバフタイプ
UENUM(BlueprintType)
enum class EFarmSlotBuffType : uint8
{
    None          UMETA(DisplayName = "無特性"),
    GrowSpeed     UMETA(DisplayName = "成長速度"),
    AttackSpeed   UMETA(DisplayName = "攻撃速度"),
    HPRate        UMETA(DisplayName = "HP割合アップ"),
    Luck          UMETA(DisplayName = "高品質確率アップ"),
};
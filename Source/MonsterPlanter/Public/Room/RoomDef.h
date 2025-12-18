#pragma once

#include "CoreMinimal.h"
#include "RoomDef.generated.h"

// 部屋のタイルサイズ
#define ROOM_TILE_SIZE 200
// 部屋のタイルの厚さ
#define ROOM_TILE_THICKNESS 100

// 部屋の種類
UENUM(BlueprintType)
enum class ERoomType : uint8
{
    Standard      UMETA(DisplayName = "スタンダード"),
    Devil         UMETA(DisplayName = "魔王部屋"),
};
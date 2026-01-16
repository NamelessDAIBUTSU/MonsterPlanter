#pragma once

#include "CoreMinimal.h"
#include "RoomDef.generated.h"

// 部屋のタイルサイズ(1辺)
#define ROOM_TILE_SIZE 100
// 部屋のタイルの厚さ
#define ROOM_TILE_THICKNESS 50
// グリッド線の厚さ
#define GRID_LINE_THICKNESS 2

// 部屋のサイズ1辺の最大cm(200 * 20タイル)
#define MAX_ROOM_SIZE 4000

// 部屋の種類
UENUM(BlueprintType)
enum class ERoomType : uint8
{
    Standard    UMETA(DisplayName = "スタンダード"),
    Farm        UMETA(DisplayName = "農場"),
    Devil       UMETA(DisplayName = "魔王部屋"),
};

// フロアタイルの種類
UENUM(BlueprintType)
enum class EFloorTileType : uint8
{
    Floor    UMETA(DisplayName = "床"),
    Soil     UMETA(DisplayName = "土壌"),
};
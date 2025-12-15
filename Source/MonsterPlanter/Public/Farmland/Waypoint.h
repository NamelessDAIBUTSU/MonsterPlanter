#pragma once

#include "CoreMinimal.h"
#include "Waypoint.generated.h"

USTRUCT(BlueprintType)
struct FWaypoint
{
	GENERATED_BODY()

public:
	FVector WaypointLocation = FVector::Zero();
	// Next をポインタにする場合の注意: 所有権とライフタイム管理を明確に
	FWaypoint* NextWaypoint = nullptr;
};
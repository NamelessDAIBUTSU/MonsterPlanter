#pragma once

#include "CoreMinimal.h"
#include "Waypoint.generated.h"

USTRUCT(BlueprintType)
struct FWaypoint
{
	GENERATED_BODY()

public:
	FVector WaypointLocation = FVector::Zero();
	int32 NextIndex = INDEX_NONE;
};
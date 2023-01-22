#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum ObstacleTypeEnum {
	ThinSmall = 0	UMETA(DisplayName = "ThinSmall"),
	ThinMedium = 1	UMETA(DisplayName = "ThinMedium"),
	ThinHuge = 2	UMETA(DisplayName = "ThinHuge"),
	WideSmall = 3	UMETA(DisplayName = "WideSmall"),
	WideMedium = 4	UMETA(DisplayName = "WideMedium"),
	WideHuge = 5	UMETA(DisplayName = "WideHuge"),
};

class REDPADPARKOUR_API ObstacleType
{
public:
	ObstacleType();
	~ObstacleType();
};

#pragma once

#include "CoreMinimal.h"
#include "ObstacleType.h"

class REDPADPARKOUR_API ParkourActions
{
public:
	ParkourActions();
	~ParkourActions();

	void obstacleTypeSelector(TEnumAsByte<ObstacleType> obstacle_type);
private:
	void thinSmallObstacle();
	void thinMediumObstacle();
	void thinHugeObstacle();
	void wideSmallObstacle();
	void wideMediumObstacle();
	void wideHugeObstacle();
};
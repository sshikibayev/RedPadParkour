#include "ParkourActions.h"

ParkourActions::ParkourActions()
{
}

ParkourActions::~ParkourActions()
{
}

void ParkourActions::obstacleTypeSelector(TEnumAsByte<ObstacleType> obstacle_type)
{
	switch (obstacle_type)
	{
	case ObstacleType::ThinSmall:
		thinSmallObstacle();
		break;
	case ObstacleType::ThinMedium:
		thinMediumObstacle();
		break;
	case ObstacleType::ThinHuge:
		thinHugeObstacle();
		break;
	case ObstacleType::WideSmall:
		wideSmallObstacle();
		break;
	case ObstacleType::WideMedium:
		wideMediumObstacle();
		break;
	case ObstacleType::WideHuge:
		wideHugeObstacle();
		break;
	default:
		break;
	}
}

void ParkourActions::thinSmallObstacle()
{
}

void ParkourActions::thinMediumObstacle()
{
}

void ParkourActions::thinHugeObstacle()
{
}

void ParkourActions::wideSmallObstacle()
{
}

void ParkourActions::wideMediumObstacle()
{
}

void ParkourActions::wideHugeObstacle()
{
}
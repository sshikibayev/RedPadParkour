#include "Obstacle.h"


AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add("Obstacle");
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TEnumAsByte<ObstacleTypeEnum> AObstacle::getObstacleType()
{
	return obstacle_type;
}
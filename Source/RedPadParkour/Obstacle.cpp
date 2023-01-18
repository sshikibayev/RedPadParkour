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

void AObstacle::interact(UCharacterMovementComponent* movement_component)
{
	movement_component_from_interaction = movement_component;
	obstacleTypeSelector();
}

void AObstacle::obstacleTypeSelector()
{
	thinSmallObstacle();
	thinMediumObstacle();
	thinHugeObstacle();
	wideSmallObstacle();
	wideMediumObstacle();
	wideHugeObstacle();
}

void AObstacle::thinSmallObstacle()
{
	if (obstacle_type == ObstacleType::ThinSmall) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Obstacle is small and thin!"));
		movement_component_from_interaction->DoJump(false);
	}
}

void AObstacle::thinMediumObstacle()
{
	if (obstacle_type == ObstacleType::ThinMedium) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Obstacle is medium and thin!"));
	}
}

void AObstacle::thinHugeObstacle()
{
	if (obstacle_type == ObstacleType::ThinHuge) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Obstacle is huge and thin!"));
	}
}

void AObstacle::wideSmallObstacle()
{
	if (obstacle_type == ObstacleType::WideSmall) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Obstacle is small and wide!"));
	}
}

void AObstacle::wideMediumObstacle()
{
	if (obstacle_type == ObstacleType::WideMedium) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Obstacle is medium and wide!"));
	}
}

void AObstacle::wideHugeObstacle()
{
	if (obstacle_type == ObstacleType::WideHuge) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Obstacle is huge and wide!"));
	}
}
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
	if (movement_component_from_interaction) {
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
}

void AObstacle::thinSmallObstacle()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Obstacle is small and thin!"));
	movement_component_from_interaction->DoJump(false);
}

void AObstacle::thinMediumObstacle()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Obstacle is medium and thin!"));	
}

void AObstacle::thinHugeObstacle()
{
	UE_LOG(LogTemp, Warning, TEXT("thinHugeObstacle"));

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Obstacle is huge and thin!"));
}

void AObstacle::wideSmallObstacle()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Obstacle is small and wide!"));
	movement_component_from_interaction->DoJump(false);
}

void AObstacle::wideMediumObstacle()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Obstacle is medium and wide!"));
}

void AObstacle::wideHugeObstacle()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Obstacle is huge and wide!"));
}
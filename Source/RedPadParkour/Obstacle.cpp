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

	playerPushForwardLogic();
}

void AObstacle::thinHugeObstacle()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Obstacle is huge and thin!"));

	playerPushForwardLogic();

	auto mesh = movement_component_from_interaction->GetOwner()->FindComponentByClass<USkeletalMeshComponent>();

	if (mesh) {
		if (hand_jumping) {
			//mesh->PlayAnimation(hand_jumping, false); //not the best way;
		}
	}
}

void AObstacle::wideSmallObstacle()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Obstacle is small and wide!"));

	movement_component_from_interaction->DoJump(false);
}

void AObstacle::wideMediumObstacle()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Obstacle is medium and wide!"));

	playerPushForwardUpLogic();
}

void AObstacle::wideHugeObstacle()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Obstacle is huge and wide!"));

	playerPushForwardUpLogic();
}

void AObstacle::playerPushForwardLogic()
{
	player = movement_component_from_interaction->GetOwner();
	FVector player_forward_vector = player->GetActorForwardVector();
	FVector current_location = player->GetActorLocation();
	FVector force_thru_obstacle = player_forward_vector * push_velocity_forward + current_location;
	player->SetActorLocation(force_thru_obstacle);
}

void AObstacle::playerPushForwardUpLogic()
{
	player = movement_component_from_interaction->GetOwner();
	FVector player_forward_vector = player->GetActorForwardVector();
	FVector player_up_vector = player->GetActorUpVector();

	FVector current_location = player->GetActorLocation();
	FVector force_thru_obstacle = (player_forward_vector * push_velocity_forward) + (player_up_vector * push_velocity_up) + current_location;
	player->SetActorLocation(force_thru_obstacle);
}


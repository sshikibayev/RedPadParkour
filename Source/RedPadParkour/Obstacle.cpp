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
	player = movement_component_from_interaction->GetOwner();
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
	movement_component_from_interaction->DoJump(false);
}

void AObstacle::thinMediumObstacle()
{
	playerPushForwardLogic();
}

void AObstacle::thinHugeObstacle()
{
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
	movement_component_from_interaction->DoJump(false);
}

void AObstacle::wideMediumObstacle()
{
	playerPushForwardUpLogic();
}

void AObstacle::wideHugeObstacle()
{
	playerPushForwardUpLogic();
}

void AObstacle::playerPushForwardLogic()
{
	FVector player_forward_vector = player->GetActorForwardVector();
	FVector current_location = player->GetActorLocation();
	FVector force_thru_obstacle = player_forward_vector * push_velocity_forward + current_location;
	player->SetActorLocation(force_thru_obstacle);
}

void AObstacle::playerPushForwardUpLogic()
{
	FVector player_forward_vector = player->GetActorForwardVector();
	FVector player_up_vector = player->GetActorUpVector();
	FVector current_location = player->GetActorLocation();
	FVector force_thru_obstacle = (player_forward_vector * push_velocity_forward) + (player_up_vector * push_velocity_up) + current_location;
	player->SetActorLocation(force_thru_obstacle);
}


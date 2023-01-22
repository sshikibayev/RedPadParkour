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

//void AObstacle::interact(UCharacterMovementComponent* movement_component, UObstacleComponent* obstacle_component)
//{
//	//movement_component_from_interaction = movement_component;
//	//player = movement_component_from_interaction->GetOwner();
//	obstacle_component->getObstacleType(obstacle_type);
//	//obstacleTypeSelector();
//}

void AObstacle::obstacleTypeSelector()
{
	/*if (movement_component_from_interaction) {
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
	}*/
}

void AObstacle::thinSmallObstacle()
{
	//actor_rotation = player->GetActorRotation(); 
	is_obstacle_thin_small = true;//switching condition in BP of the char; 
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AObstacle::switchAnimation, 1.0f, true, 1.59f);
}

void AObstacle::thinMediumObstacle()
{
}

void AObstacle::thinHugeObstacle()
{
}

void AObstacle::wideSmallObstacle()
{
}

void AObstacle::wideMediumObstacle()
{
}

void AObstacle::wideHugeObstacle()
{
}

void AObstacle::playerPushForwardLogic()
{
	FVector player_location = player->GetActorLocation();
	FVector obstacle_location = GetActorLocation();
	FRotator look_at_rotation = UKismetMathLibrary::FindLookAtRotation(player_location, obstacle_location);
	UE_LOG(LogTemp, Warning, TEXT("look_at_rotation: %s"), *look_at_rotation.ToString());

	FRotator player_rotation = FRotator(0, look_at_rotation.Yaw, 0);
	UE_LOG(LogTemp, Warning, TEXT("Rot: %s"), *player_rotation.ToString());
	player->SetActorRotation(player_rotation);

	FVector player_forward_vector = player->GetActorForwardVector();
	FVector force_thru_obstacle = player_forward_vector * push_velocity_forward + player_location;
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

void AObstacle::switchAnimation() {
	is_obstacle_thin_small = false;
	GetWorldTimerManager().ClearTimer(TimerHandle);
	//player->SetActorRelativeRotation(FRotator(0, actor_rotation.Yaw, 0));
}
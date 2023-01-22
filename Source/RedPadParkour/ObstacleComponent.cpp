#include "ObstacleComponent.h"

UObstacleComponent::UObstacleComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UObstacleComponent::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner();
	movement_component = owner->FindComponentByClass<UCharacterMovementComponent>();

	setupCollision();
	if (GetWorld()) {
		findSwitcher();
	}
}

void UObstacleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UObstacleComponent::setupCollision()
{
	collision_box = owner->FindComponentByClass<UBoxComponent>();
	if (collision_box) {
		collision_box->SetCollisionProfileName(TEXT("Trigger"));

		collision_box->OnComponentBeginOverlap.AddDynamic(this, &UObstacleComponent::OnBeginOverlap);
		collision_box->OnComponentEndOverlap.AddDynamic(this, &UObstacleComponent::OnEndOverlap);
	}
}

void UObstacleComponent::findSwitcher()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStateSwitcher::StaticClass(), found_switchers);

	if (found_switchers.Num() <= 0) {
		UE_LOG(LogTemp, Error, TEXT("No switchers were found"));
	}
	else if (found_switchers.Num() > 1) {
		UE_LOG(LogTemp, Error, TEXT("More then one switcher were found"));
	}
	else {
		for (auto switcher : found_switchers) {
			state_switcher = Cast<AStateSwitcher>(switcher);
		}
	}
}

void UObstacleComponent::OnBeginOverlap(UPrimitiveComponent* overlapped_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 body_index, bool from_sweep, const FHitResult& hit_result)
{
	if (is_actor_valid(other_actor, other_component) && is_actor_able_to_parkour()) {
		startInteraction(other_actor);
    }
}

void UObstacleComponent::OnEndOverlap(UPrimitiveComponent* overlapped_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 body_index)
{
	if (is_interaction_started) {
		is_interaction_started = false;
		changeState(StateType::Active);
	}
}

bool UObstacleComponent::is_actor_valid(AActor* other_actor, UPrimitiveComponent* other_component)
{
	bool is_actor_valid = other_actor && other_actor != owner && other_component;
	bool is_actor_has_valid_tag = other_actor->ActorHasTag(obstacle_tag);
	return is_actor_valid && is_actor_has_valid_tag;
}

bool UObstacleComponent::is_actor_able_to_parkour()
{
	bool is_grounded = movement_component->IsMovingOnGround();
	return is_grounded;
}

void UObstacleComponent::startInteraction(AActor* obstacle) {
	if (obstacle && !is_interaction_started) {
		is_interaction_started = true;
		changeState(StateType::Interaction);
		auto interacted_obstacle = Cast<AObstacle>(obstacle);
		obstacleTypeSelector(interacted_obstacle->getObstacleType());
	}
}

void UObstacleComponent::changeState(StateType state)
{
	if (state_switcher) {
		state_switcher->setState(state);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("StateSwitcher is obstacle component is not valid or empty"));
	}
}

void UObstacleComponent::obstacleTypeSelector(TEnumAsByte<ObstacleTypeEnum> obstacle_type)
{
	switch (obstacle_type)
	{
	case ObstacleTypeEnum::ThinSmall:
		thinSmallObstacle();
		break;
	case ObstacleTypeEnum::ThinMedium:
		thinMediumObstacle();
		break;
	case ObstacleTypeEnum::ThinHuge:
		thinHugeObstacle();
		break;
	case ObstacleTypeEnum::WideSmall:
		wideSmallObstacle();
		break;
	case ObstacleTypeEnum::WideMedium:
		wideMediumObstacle();
		break;
	case ObstacleTypeEnum::WideHuge:
		wideHugeObstacle();
		break;
	default:
		break;
	}
}

void UObstacleComponent::thinSmallObstacle()
{
	is_obstacle_thin_small = true;//switching condition in BP of the char; 
}

void UObstacleComponent::thinMediumObstacle()
{
}

void UObstacleComponent::thinHugeObstacle()
{
}

void UObstacleComponent::wideSmallObstacle()
{
}

void UObstacleComponent::wideMediumObstacle()
{
}

void UObstacleComponent::wideHugeObstacle()
{
}
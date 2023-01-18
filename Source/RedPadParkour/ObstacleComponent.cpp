#include "ObstacleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UObstacleComponent::UObstacleComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UObstacleComponent::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner();
	setupCollision();
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

void UObstacleComponent::startInteraction() {
	if (interacted_obstacle) {
		interacted_obstacle->interact(owner->FindComponentByClass<UCharacterMovementComponent>());
	}
}

void UObstacleComponent::OnBeginOverlap(UPrimitiveComponent* overlapped_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 body_index, bool from_sweep, const FHitResult& hit_result)
{
	if (is_actor_valid(other_actor, other_component) && is_actor_able_to_parkour()) {
		if (other_actor->ActorHasTag(obstacle_tag)) {
			interacted_obstacle = Cast<AObstacle>(other_actor);
			startInteraction();
			disableInput();
		}
    }
}

bool UObstacleComponent::is_actor_valid(AActor* other_actor, UPrimitiveComponent* other_component)
{
	return other_actor && other_actor != owner && other_component;
}

bool UObstacleComponent::is_actor_able_to_parkour()
{
	auto character_movement_component = owner->FindComponentByClass<UCharacterMovementComponent>();
	bool is_grounded = character_movement_component->IsMovingOnGround();

	return is_grounded;
}

void UObstacleComponent::enableInput()
{
	if (GetWorld()) {
		player_controller = GetWorld()->GetFirstPlayerController();
		owner->EnableInput(player_controller);
	}
}

void UObstacleComponent::disableInput()
{
	if (GetWorld()) {
		player_controller = GetWorld()->GetFirstPlayerController();
		owner->DisableInput(player_controller);
	}
}

void UObstacleComponent::OnEndOverlap(UPrimitiveComponent* overlapped_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 body_index)
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Overlapped end"));
	}

	enableInput();
}
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
			//disableInput();
			changeState(StateType::Interaction);
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
		auto pawn = player_controller->GetPawn();
		pawn->EnableInput(player_controller);
	}
}

void UObstacleComponent::disableInput()
{
	if (GetWorld()) {
		player_controller = GetWorld()->GetFirstPlayerController();
		auto pawn = player_controller->GetPawn();
		pawn->DisableInput(player_controller);
	}
}

void UObstacleComponent::changeState(StateType state)
{
	UE_LOG(LogTemp, Error, TEXT("Change state laucnhed"));

	if (state_switcher) {
		state_switcher->setState(state);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("StateSwitcher is obstacle component is not valid or empty"));
	}
}

void UObstacleComponent::OnEndOverlap(UPrimitiveComponent* overlapped_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 body_index)
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Overlapped end"));
	}

	//enableInput();
	changeState(StateType::Active);
}
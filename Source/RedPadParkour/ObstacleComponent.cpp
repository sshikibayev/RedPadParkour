#include "ObstacleComponent.h"

UObstacleComponent::UObstacleComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UObstacleComponent::BeginPlay()
{
	Super::BeginPlay();

	setupCollision();
}

void UObstacleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UObstacleComponent::setupCollision()
{
	collision_box = GetOwner()->FindComponentByClass<UBoxComponent>();
	if (collision_box) {
		collision_box->SetCollisionProfileName(TEXT("Trigger"));

		collision_box->OnComponentBeginOverlap.AddDynamic(this, &UObstacleComponent::OnBeginOverlap);
		collision_box->OnComponentEndOverlap.AddDynamic(this, &UObstacleComponent::OnEndOverlap);
	}
}

void UObstacleComponent::OnBeginOverlap(UPrimitiveComponent* overlapped_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 body_index, bool from_sweep, const FHitResult& hit_result)
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Overlapped begin"));
	}
}

void UObstacleComponent::OnEndOverlap(UPrimitiveComponent* overlapped_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 body_index)
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Overlapped end"));
	}
}
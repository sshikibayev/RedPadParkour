#include "ObstacleComponent.h"

UObstacleComponent::UObstacleComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UObstacleComponent::BeginPlay()
{
	Super::BeginPlay();	
}


void UObstacleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
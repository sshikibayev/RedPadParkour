#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "Obstacle.h"
#include "StateSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "ObstacleComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class REDPADPARKOUR_API UObstacleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UObstacleComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	AActor* owner;
	FName obstacle_tag{ "obstacle" };
	AObstacle* interacted_obstacle;
	UBoxComponent* collision_box;
	AStateSwitcher* state_switcher;
	TArray<AActor*> found_switchers;
	bool is_interaction_started{ false };

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* overlapped_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 body_index, bool from_sweep, const FHitResult& hit_result);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* overlapped_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 body_index);

	void setupCollision();
	void findSwitcher();
	bool is_actor_valid(AActor* other_actor, UPrimitiveComponent* other_component);
	bool is_actor_able_to_parkour();
	void startInteraction();
	void changeState(StateType state);
};
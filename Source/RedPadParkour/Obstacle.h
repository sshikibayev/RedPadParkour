#pragma once

UENUM(BlueprintType)
enum class ObstacleType : uint8 {
	ThinSmall	UMETA(DisplayName = "ThinSmall"),
	ThinMedium	UMETA(DisplayName = "ThinMedium"),
	ThinHuge	UMETA(DisplayName = "ThinHuge"),
	WideSmall	UMETA(DisplayName = "WideSmall"),
	WideMedium	UMETA(DisplayName = "WideMedium"),
	WideHuge	UMETA(DisplayName = "WideHuge"),
};

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Obstacle.generated.h"


UCLASS()
class REDPADPARKOUR_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacle();
	virtual void Tick(float DeltaTime) override;
	void interact(UCharacterMovementComponent* movement_component);

	UPROPERTY(EditAnywhere, Category = "Obstacle type")
	ObstacleType obstacle_type;

protected:
	virtual void BeginPlay() override;

private:
	UCharacterMovementComponent* movement_component_from_interaction;

	void obstacleTypeSelector();
	void thinSmallObstacle();
	void thinMediumObstacle();
	void thinHugeObstacle();
	void wideSmallObstacle();
	void wideMediumObstacle();
	void wideHugeObstacle();
};
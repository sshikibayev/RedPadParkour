#pragma once

UENUM(BlueprintType)
enum ObstacleType{
	ThinSmall = 0	UMETA(DisplayName = "ThinSmall"),
	ThinMedium = 1	UMETA(DisplayName = "ThinMedium"),
	ThinHuge = 2	UMETA(DisplayName = "ThinHuge"),
	WideSmall = 3	UMETA(DisplayName = "WideSmall"),
	WideMedium = 4	UMETA(DisplayName = "WideMedium"),
	WideHuge = 5	UMETA(DisplayName = "WideHuge"),
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
	TEnumAsByte <ObstacleType> obstacle_type;

	UPROPERTY(EditAnywhere, Category = "Obstacle push")
	float push_velocity_forward{ 100 };
	UPROPERTY(EditAnywhere, Category = "Obstacle push")
	float push_velocity_up{ 100 };

	UPROPERTY(EditAnywhere)
	class UAnimationAsset* hand_jumping;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UCharacterMovementComponent* movement_component_from_interaction;
	UPROPERTY()
	AActor* player;

	void obstacleTypeSelector();
	void thinSmallObstacle();
	void thinMediumObstacle();
	void thinHugeObstacle();
	void wideSmallObstacle();
	void wideMediumObstacle();
	void wideHugeObstacle();
	void playerPushForwardLogic();
	void playerPushForwardUpLogic();
};
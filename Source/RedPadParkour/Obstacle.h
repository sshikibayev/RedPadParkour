#pragma once

#include "CoreMinimal.h"
#include "ObstacleType.h"

#include "Obstacle.generated.h"


UCLASS()
class REDPADPARKOUR_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacle();
	virtual void Tick(float DeltaTime) override;

	TEnumAsByte <ObstacleTypeEnum> getObstacleType();

	UPROPERTY(EditAnywhere, Category = "Obstacle type")
	TEnumAsByte <ObstacleTypeEnum> obstacle_type;

protected:
	virtual void BeginPlay() override;
};
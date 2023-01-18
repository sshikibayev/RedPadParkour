#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class REDPADPARKOUR_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacle();
	void printMessage();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
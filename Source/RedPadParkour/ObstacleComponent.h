#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObstacleComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REDPADPARKOUR_API UObstacleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UObstacleComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
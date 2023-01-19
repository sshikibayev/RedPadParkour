#pragma once

UENUM(BlueprintType)
enum StateType {
	Active = 0	UMETA(DisplayName = "Active state"),
	Interaction = 1	UMETA(DisplayName = "Interaction state"),
};

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StateSwitcher.generated.h"

UCLASS()
class REDPADPARKOUR_API AStateSwitcher : public AActor
{
	GENERATED_BODY()
	
public:	
	AStateSwitcher();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	APlayerController* player_controller;

	StateType getState();
	void setState(StateType state);

protected:
	virtual void BeginPlay() override;

private:
	TEnumAsByte<StateType> state_type{ StateType::Active };

	UPROPERTY()
	APawn* pawn;

	void setupPawn();
	void switchState();
};
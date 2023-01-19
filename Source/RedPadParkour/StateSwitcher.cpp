#include "StateSwitcher.h"

AStateSwitcher::AStateSwitcher()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStateSwitcher::BeginPlay()
{
	Super::BeginPlay();	

	player_controller = GetWorld()->GetFirstPlayerController();
	setupPawn();
}

void AStateSwitcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

StateType AStateSwitcher::getState()
{
	return state_type;
}

void AStateSwitcher::setState(StateType state)
{
	state_type = state;
	switchState();
}

void AStateSwitcher::setupPawn()
{
	if (player_controller) {
		pawn = player_controller->GetPawn();
	}
}

void AStateSwitcher::switchState()
{
	if (GetWorld() && pawn) {
		switch (state_type)
		{
		case StateType::Active:
			//pawn->EnableInput(player_controller);
			break;
		case StateType::Interaction:
			//pawn->DisableInput(player_controller);
			break;
		default:
			break;
		}
	}
}
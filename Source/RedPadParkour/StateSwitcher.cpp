#include "StateSwitcher.h"

AStateSwitcher::AStateSwitcher()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStateSwitcher::BeginPlay()
{
	Super::BeginPlay();	

	player_controller = GetWorld()->GetFirstPlayerController();
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

void AStateSwitcher::switchState()
{
	if (state_type == StateType::Active) {
		if (GetWorld()) {
			auto pawn = player_controller->GetPawn();
			pawn->EnableInput(player_controller);

		}
	}
	else {
		if (GetWorld()) {	
			auto pawn = player_controller->GetPawn();
			pawn->DisableInput(player_controller);
		}
	}
}

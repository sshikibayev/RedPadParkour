#include "StateSwitcher.h"

AStateSwitcher::AStateSwitcher()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStateSwitcher::BeginPlay()
{
	Super::BeginPlay();	

	player_controller = GetWorld()->GetFirstPlayerController();
	if (player_controller) {
		pawn = player_controller->GetPawn();
	}
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
	UE_LOG(LogTemp, Warning, TEXT("Switch state: %s"), *pawn->GetName());
	if (state_type == StateType::Active) {
		if (GetWorld() && pawn) {
			pawn->EnableInput(player_controller);
			UE_LOG(LogTemp, Warning, TEXT("Enable state"))
		}
	}
	else {
		if (GetWorld() && pawn) {
			pawn->DisableInput(player_controller);
			UE_LOG(LogTemp, Warning, TEXT("Disable state"))
		}
	}
}
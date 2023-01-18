// Copyright Epic Games, Inc. All Rights Reserved.

#include "RedPadParkourGameMode.h"
#include "RedPadParkourCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARedPadParkourGameMode::ARedPadParkourGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

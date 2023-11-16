// Copyright Epic Games, Inc. All Rights Reserved.

#include "USBGameMode.h"
#include "USBCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUSBGameMode::AUSBGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

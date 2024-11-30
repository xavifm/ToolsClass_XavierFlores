// Copyright Epic Games, Inc. All Rights Reserved.

#include "ToolsClassGameMode.h"
#include "ToolsClassCharacter.h"
#include "UObject/ConstructorHelpers.h"

AToolsClassGameMode::AToolsClassGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

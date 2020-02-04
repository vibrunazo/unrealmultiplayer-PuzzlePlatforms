// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "PuzzlePlatformsGameMode.h"
#include "PuzzlePlatformsCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "PuzzleController.h"

APuzzlePlatformsGameMode::APuzzlePlatformsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	// static ConstructorHelpers::FClassFinder<APuzzleController> ControllerClass(TEXT("Class'/Script/PuzzlePlatforms.PuzzleController'"));
	// if (ControllerClass.Class != NULL)
	// {
	// 	PlayerControllerClass = ControllerClass.Class;
	// }
	PlayerControllerClass = APuzzleController::StaticClass();
	// bUseSeamlessTravel = true;
}

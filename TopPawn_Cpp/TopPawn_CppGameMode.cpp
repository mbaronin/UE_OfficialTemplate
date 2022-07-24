// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopPawn_CppGameMode.h"
#include "TopPawn_CppPlayerController.h"
#include "TopPawn_CppCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATopPawn_CppGameMode::ATopPawn_CppGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATopPawn_CppPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}
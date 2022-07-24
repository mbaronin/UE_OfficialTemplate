// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SelectLevelCore/SelectLevelGameModeBase.h"
#include "UI/SelectLevelUI/Core/SelectLevelHUD.h"
#include "Core/HallCore/HallPlayerController.h"
#include "Core/HallCore/HallPawn.h"



ASelectLevelGameModeBase::ASelectLevelGameModeBase()
{
	HUDClass = ASelectLevelHUD::StaticClass();
	DefaultPawnClass = AHallPawn::StaticClass();
	PlayerControllerClass = AHallPlayerController::StaticClass();

		
}

void ASelectLevelGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}

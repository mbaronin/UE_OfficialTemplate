// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HallCore/HallGameModeBase.h"


#include "Core/HallCore/HallPlayerController.h"
#include "Core/HallCore/HallPawn.h"
#include "UI/HallUI/Core/HallHUD.h"

AHallGameModeBase::AHallGameModeBase()
{
	DefaultPawnClass = AHallPawn::StaticClass();
	HUDClass = AHallHUD::StaticClass();
	PlayerControllerClass = AHallPlayerController::StaticClass();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "HowToUMG/HowToUMGPlayerController.h"

void AHowToUMGPlayerController::BeginPlay()
{
    Super::BeginPlay();
    SetInputMode(FInputModeGameAndUI());
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameUI/Core/RuleofTheHUD.h"

#include "UObject/ConstructorHelpers.h"
#include "UI\GameUI\UMG\UI_MainScreen.h"






ARuleofTheHUD::ARuleofTheHUD()
{

	static ConstructorHelpers::FClassFinder<UUI_MainScreen> MainScreen_BPClass(TEXT("/Game/UI/Game/UI_MainScreen_BP"));
	
	MainScreenClass = MainScreen_BPClass.Class;
}



void ARuleofTheHUD::BeginPlay()
{
	Super::BeginPlay();

	//¹ØÁªHUD Óë UMG
	MainScreen = CreateWidget<UUI_MainScreen>(GetWorld(), MainScreenClass);
	MainScreen->AddToViewport();


}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameCore/TowerDefenceGameInstance.h"
//#include "F:\ue\slefuegame\Business_process_2\Plugins\SimpleScreenLoading\Source\SimpleScreenLoading\Public\SimpleScreenLoading.h"
#include "SimpleScreenLoading.h"

UTowerDefenceGameInstance::UTowerDefenceGameInstance()
	: /*ISimpleArchivesInterface()
	, */SaveSlotNumber(INDEX_NONE)
	, GameSaveType(EGameSaveType::NONE)
{

}
void UTowerDefenceGameInstance::Init() 
{
	Super::Init();

	FSimpleScreenLoadingModule& SimpleSvreenLoadingModule = FModuleManager::LoadModuleChecked<FSimpleScreenLoadingModule>("SimpleScreenLoading");
	SimpleSvreenLoadingModule.SetupScreenLoading();
}

int32 UTowerDefenceGameInstance::GetCurrentSaveSlotNumber() const
{
	return SaveSlotNumber;
}

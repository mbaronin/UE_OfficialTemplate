// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Save/SaveGameCore.h"			//rule of save
#include "Data/Save/SaveStruct.h"			//struct
#include "GameSaveSlotList.generated.h"



UCLASS()
class BUSINESS_PROCESS_2_API UGameSaveSlotList : public USaveGameCore
{
	GENERATED_BODY()

public:
	UPROPERTY(SaveGame)//�ᱨ��? //ҪUSTRUCT�ṹ������÷���
	FSaveSlotList SlotList;

	virtual void InitSaveGame(UWorld *InWorld);

	virtual void InitSaveGameFromArchives(UWorld *InWorld);
};



// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Save/SaveGameCore.h"			//rule of save
#include "Data/Core/CharacterData.h"		//��ɫ����


#include "Data/Core/GameData.h"		

#include "GameSaveData.generated.h"

/**
 * 
 */
UCLASS()
class BUSINESS_PROCESS_2_API UGameSaveData : public USaveGameCore
{
	GENERATED_BODY()
	
public:
	//��Ϸ�����еĽ�ɫ
	UPROPERTY(SaveGame)
	TMap<FGuid,FCharacterData> CharacterDatas;

	//��ǰ�ؿ�����Ϸ����(�洢��gamedata��)
	UPROPERTY(SaveGame)
	FGameInstanceDatas GameDatas;

	virtual void InitSaveGame(UWorld *InWorld);
};

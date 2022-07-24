// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Save/SaveGameCore.h"			//rule of save
#include "Data/Core/CharacterData.h"		//角色数据


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
	//游戏场景中的角色
	UPROPERTY(SaveGame)
	TMap<FGuid,FCharacterData> CharacterDatas;

	//当前关卡内游戏数据(存储在gamedata中)
	UPROPERTY(SaveGame)
	FGameInstanceDatas GameDatas;

	virtual void InitSaveGame(UWorld *InWorld);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Save/SaveGameCore.h"

#include "Data/Core/BuildingTowerData.h"		//建造栏
#include "Data\Core\PlayerSkillData.h"//技能栏
#include "Data\Core\PlayerData.h"


#include "PlayerSaveData.generated.h"



/**
 * 
 */
UCLASS()
class BUSINESS_PROCESS_2_API UPlayerSaveData : public USaveGameCore
{
	GENERATED_BODY()

public:
	
	//玩家账户数据
	UPROPERTY(SaveGame)
	FPlayerData PlayerData;

	//建造栏 (背包数据)
	UPROPERTY(SaveGame)
	TMap<FGuid, FBuildingTower> BuildingTowers;

	//技能栏  (玩家游戏中数据的状态)
	UPROPERTY(SaveGame)
	TMap<FGuid, FPlayerSkillData> PlayerSkillDatas;

	virtual void InitSaveGame(UWorld *InWorld);

	void AddPlayerSkill(UWorld *InWorld, const FGuid *Guid, int32 SkillID);




};

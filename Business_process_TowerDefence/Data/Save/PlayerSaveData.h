// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Save/SaveGameCore.h"

#include "Data/Core/BuildingTowerData.h"		//������
#include "Data\Core\PlayerSkillData.h"//������
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
	
	//����˻�����
	UPROPERTY(SaveGame)
	FPlayerData PlayerData;

	//������ (��������)
	UPROPERTY(SaveGame)
	TMap<FGuid, FBuildingTower> BuildingTowers;

	//������  (�����Ϸ�����ݵ�״̬)
	UPROPERTY(SaveGame)
	TMap<FGuid, FPlayerSkillData> PlayerSkillDatas;

	virtual void InitSaveGame(UWorld *InWorld);

	void AddPlayerSkill(UWorld *InWorld, const FGuid *Guid, int32 SkillID);




};

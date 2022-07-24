// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Core/RuleOfThePlayerState.h"

#include "Data/Save/PlayerSaveData.h"
#include "Data/Core/BuildingTowerData.h"		//������

#include "TowerDefencePlayerState.generated.h"

/**
 * 
 */

UCLASS()
class BUSINESS_PROCESS_2_API ATowerDefencePlayerState : public ARuleOfThePlayerState
{
	GENERATED_BODY()
	
//		//��ҵļ���
//		UPROPERTY()
//		UDataTable* PlayerSkillDataTable;
//
public:
//	ATowerDefencePlayerState();
//	virtual void BeginPlay() override;
//
//	virtual bool SaveGameData(int32 SaveNumber);
//
//	virtual bool ReadGameData(int32 SaveNumber);
//
//	const TArray<FPlayerSkillData*>& GetPlayerSkillDataFormTable();
//	const FPlayerSkillData* GetPlayerSkillDataFormTable(const int32& PlayerSkillID);
//
//	FPlayerSkillData* GetPlayerSkillData(const FGuid& PlayerSkillGUID);
//
//	bool IsVerificationSkill(const FGuid& SlotID);
//	void UsePlayerSkill(const FGuid& SlotID);
//	void AddPlayerSkill(const FGuid* Guid, int32 SkillID);
//
	FBuildingTower& GetBuildingTower(const FGuid& ID);
	FPlayerData& GetPlayerData();
	const FBuildingTower& AddBuildingTower(const FGuid& ID, const FBuildingTower& Data);

	//���������� �������ID������
	const TArray<const FGuid*> GetBuildingTowersID();
	void RequestInventorySlotSwap(const FGuid& A, const FGuid& B);
	FBuildingTower& GetBuildingTowerNULL();
	UPlayerSaveData* GetSaveData();
//	FPlayerSkillData* GetSkillDatas(const FGuid& SkillGuid);
//	const TArray<const FGuid*> GetSkillDatasID();
	UFUNCTION(/*Server*/)
		void TowersPrepareBuildingNumber(const FGuid& InventoryGUID);
//
	UFUNCTION(/*Server*/)
		void SetTowersDragICONState(const FGuid& InventoryGUID, bool bDragICO);

	UFUNCTION(/*Server*/)
		void TowersConstructionNumber(const FGuid& InventoryGUID, int32 InValue = INDEX_NONE);
protected:
	UPROPERTY()
		UPlayerSaveData* SaveData;

private:
	UPROPERTY()
		FBuildingTower BuildingTowerNULL;

//	TArray<FPlayerSkillData*> CachePlayerSkilDatas;

};

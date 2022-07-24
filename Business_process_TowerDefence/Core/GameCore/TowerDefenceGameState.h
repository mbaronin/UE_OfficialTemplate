// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/RuleOfTheGameState.h"
#include "GameFramework/GameStateBase.h"

#include "Data/Core/CharacterData.h"		//角色数据 待删除
#include "Business_process_2\EnumType.h"
//data
#include "Data/Core/SkillData.h"
#include "Data/Save/GameSaveData.h"
#include "Data/Core/GameData.h"

#include "TowerDefenceGameState.generated.h"

/**
 * 
 */

class UGameSaveData;
class UGameSaveSlotList;
class ARuleOfTheCharacter;
class UDataTable;

class AMonster;
class ATowers;
struct FSkillData;
//ARuleOfTheGameState
UCLASS()
class BUSINESS_PROCESS_2_API ATowerDefenceGameState : public ARuleOfTheGameState//AGameStateBase
{
	GENERATED_BODY()

	friend class ABusiness_process_2GameModeBase;

	///数据库(数值表)

	//塔数据
	UPROPERTY()
	UDataTable* AITowerCharacterData;
	//怪物数据
	UPROPERTY()
	UDataTable* AIMonsterCharacterData;
	//角色的技能
	UPROPERTY()
	UDataTable* SkillCharacterData;

public:
	ATowerDefenceGameState();

	//将table数据转入缓存池
	const TArray<FCharacterData*>& GetTowerDataFormTable();
	const TArray<FCharacterData*>& GetMonsterDataFormTable();


public:
	//利用hash进行"增删查改"
	FCharacterData* AddCharacterData(const FGuid& ID, const FCharacterData& Data);
	bool RemoveCharacterData(const FGuid& ID);
	FCharacterData* GetCharacterData(const FGuid& ID);

	const FCharacterData* GetCharacterDataByID(int32 ID, ECharacterType Type = ECharacterType::TOWER);


public:

	///存档 数据

	//保存&读取
	virtual	bool SaveGameData(int32 SaveNumber);
	virtual	bool ReadGameData(int32 SaveNumber);



	///技能

	//模板技能
	const TArray<FSkillData*>& GetSkillDataFormTable();

	const FSkillData* GetSkillData(const int32& SkillID);


public:
	

	FGameInstanceDatas& GetGameData();

	////动态技能的操作
	//FSkillData* AddSkillData(const FGuid& CharacterID, const FGuid& SkillID, const FSkillData& Data);
	////FSkillData* GetSkillData(const FGuid& SkillID);
	//const FSkillData* GetSkillData(const int32& SkillID);
	//FSkillData* GetSkillData(const FGuid& CharacterID, const FGuid& SkillID);
	//int32 RemoveSkillData(const FGuid& SkillID);

	//UFUNCTION(/*Server*/)
	//	void AddSkillDataTemplateToCharacterData(const FGuid& CharacterID, int32 SkillID);

	//bool IsVerificationSkillTemplate(const FGuid& CharacterID, int32 SkillID);
	//bool IsVerificationSkillTemplate(const FCharacterData& CharacterData, int32 SkillID);
	//bool IsVerificationSkill(const FCharacterData& CharacterSkill, int32 SkillID);
	//bool IsVerificationSkill(const FGuid& CharacterID, int32 SkillID);

	//const TMap<FGuid, FCharacterData>& GetCharacterDatas();

	//UFUNCTION(/*Server*/)
	//	bool SetSubmissionDataType(FGuid CharacterID, int32 Skill, ESubmissionSkillRequestType Type);

	//void AddSkill(const FGuid& CharacterGUID, int32 InSkillID);
	//void AddSkill(TPair<FGuid, FCharacterData>& Owner, const FSkillData& InSkill);



protected:
	//获取存档
	UFUNCTION(BlueprintCallable)//测试用
	UGameSaveData* GetSaveData();


private:
	UPROPERTY()
		UGameSaveData* SaveData;

	//缓存池
	TArray<FCharacterData*> CacheTowerDatas;
	TArray<FCharacterData*> CacheMonsterDatas;
	TArray<FSkillData*> CacheSkillDatas;




																		  
																											  



};

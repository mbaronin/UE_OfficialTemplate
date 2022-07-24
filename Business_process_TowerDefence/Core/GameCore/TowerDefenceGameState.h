// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/RuleOfTheGameState.h"
#include "GameFramework/GameStateBase.h"

#include "Data/Core/CharacterData.h"		//��ɫ���� ��ɾ��
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

	///���ݿ�(��ֵ��)

	//������
	UPROPERTY()
	UDataTable* AITowerCharacterData;
	//��������
	UPROPERTY()
	UDataTable* AIMonsterCharacterData;
	//��ɫ�ļ���
	UPROPERTY()
	UDataTable* SkillCharacterData;

public:
	ATowerDefenceGameState();

	//��table����ת�뻺���
	const TArray<FCharacterData*>& GetTowerDataFormTable();
	const TArray<FCharacterData*>& GetMonsterDataFormTable();


public:
	//����hash����"��ɾ���"
	FCharacterData* AddCharacterData(const FGuid& ID, const FCharacterData& Data);
	bool RemoveCharacterData(const FGuid& ID);
	FCharacterData* GetCharacterData(const FGuid& ID);

	const FCharacterData* GetCharacterDataByID(int32 ID, ECharacterType Type = ECharacterType::TOWER);


public:

	///�浵 ����

	//����&��ȡ
	virtual	bool SaveGameData(int32 SaveNumber);
	virtual	bool ReadGameData(int32 SaveNumber);



	///����

	//ģ�弼��
	const TArray<FSkillData*>& GetSkillDataFormTable();

	const FSkillData* GetSkillData(const int32& SkillID);


public:
	

	FGameInstanceDatas& GetGameData();

	////��̬���ܵĲ���
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
	//��ȡ�浵
	UFUNCTION(BlueprintCallable)//������
	UGameSaveData* GetSaveData();


private:
	UPROPERTY()
		UGameSaveData* SaveData;

	//�����
	TArray<FCharacterData*> CacheTowerDatas;
	TArray<FCharacterData*> CacheMonsterDatas;
	TArray<FSkillData*> CacheSkillDatas;




																		  
																											  



};

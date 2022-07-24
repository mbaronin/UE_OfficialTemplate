// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameCore/TowerDefenceGameState.h"

#include "Core/GameCore/TowerDefenceGameInstance.h"

#include "Business_process_2/FunctionUtils.h"
#include "Business_process_2\Macro.h"		//通用宏
#include "UObject/ConstructorHelpers.h"		//获取数据库

#include "Data/Save/GameSaveData.h"			//存档

#include "Kismet/GameplayStatics.h"			//读取 存储
#include "Data/Save/GameSaveSlotList.h"		//存档位

#include "Character/Core/RuleOfTheCharacter.h" //生成角色
#include "Engine/DataTable.h"		//数据库
//
//#include "Character/CharacterCore/Monster.h"
//#include "Character/CharacterCore/Towers.h"






ATowerDefenceGameState::ATowerDefenceGameState()
{
	PrimaryActorTick.bCanEverTick = true;

	//获取数据库
	static ConstructorHelpers::FObjectFinder<UDataTable> MyTable_Towers(TEXT("/Game/Character/CharacterData/TowersData")); 
	static ConstructorHelpers::FObjectFinder<UDataTable> MyTable_Monsters(TEXT("/Game/Character/CharacterData/MonsterData")); 
	static ConstructorHelpers::FObjectFinder<UDataTable> MyTable_Skill(TEXT("/Game/Character/CharacterData/CharacterSkillData")); 
	AITowerCharacterData	=		MyTable_Towers.Object;
	AIMonsterCharacterData	=		MyTable_Monsters.Object;
	SkillCharacterData		=		MyTable_Skill.Object;
}



FCharacterData* ATowerDefenceGameState::AddCharacterData(const FGuid& ID, const FCharacterData& Data)
{
    
	return &GetSaveData()->CharacterDatas.Add(ID, Data);
}

bool ATowerDefenceGameState::RemoveCharacterData(const FGuid& ID)
{
    
	return GetSaveData()->CharacterDatas.Remove(ID) >= 0;
}

FCharacterData* ATowerDefenceGameState::GetCharacterData(const FGuid& ID)
{
	
	//这里程序开始读取不到 数据
	if (GetSaveData()->CharacterDatas.Contains(ID))
	{
		if (&GetSaveData()->CharacterDatas[ID])
		{
			return &GetSaveData()->CharacterDatas[ID];
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("ID is empty!"));
		}

	}
	////报错
	//Macro_print(Error, "The current [%s] is invalid",*ID.ToString());
	return nullptr; 
}

const FCharacterData* ATowerDefenceGameState::GetCharacterDataByID(int32 ID, ECharacterType Type)
{
	auto GetMyCharacterData = [&](const TArray< FCharacterData*>& Datas, int32 ID)->const FCharacterData*
	{
		for (const auto& Tmp : Datas)
		{
			if (Tmp->ID == ID)
			{
				return Tmp;
			}
		}

		return nullptr;
	};

	switch (Type)
	{
	case ECharacterType::TOWER:
	{
		const TArray< FCharacterData*>& Datas = GetTowerDataFormTable();
		return GetMyCharacterData(Datas, ID);
	}
	case ECharacterType::MONSTER:
	{
		const TArray< FCharacterData*>& Datas = GetMonsterDataFormTable();
		return GetMyCharacterData(Datas, ID);
	}
	}
	
	return nullptr;
}


UGameSaveData* ATowerDefenceGameState::GetSaveData()
{
	//创建SaveData
	if (!SaveData)
	{
		
		if (UTowerDefenceGameInstance* InGameInstance = GetWorld()->GetGameInstance<UTowerDefenceGameInstance>())
		{
			SaveData = FunctionUtils::GetSave<UGameSaveData>(
				GetWorld(),
				TEXT("SaveSlot_%i"),
				InGameInstance->GetCurrentSaveSlotNumber(),
				InGameInstance->GetGameType());
		}
	}

	return SaveData;
}

bool ATowerDefenceGameState::SaveGameData(int32 SaveNumber)
{
	/*if (SaveData && SlotList)
	{
		SlotList->SlotList.AddGameDataByNumber(SaveNumber);

		return UGameplayStatics::SaveGameToSlot(SlotList, FString::Printf(TEXT("SlotList")), 0)
			&& UGameplayStatics::SaveGameToSlot(SaveData, FString::Printf(TEXT("SaveSlot_%i"), SaveNumber), 0);
	}*/
	return false;
}

bool ATowerDefenceGameState::ReadGameData(int32 SaveNumber)
{
	SaveData = Cast<UGameSaveData>(UGameplayStatics::LoadGameFromSlot(FString::Printf(TEXT("SaveSlot_%i"), SaveNumber), 0));
	return SaveData != NULL;
}

const TArray<FSkillData*>& ATowerDefenceGameState::GetSkillDataFormTable()
{
	if (!CacheSkillDatas.Num())
	{
		SkillCharacterData->GetAllRows(TEXT("Slill Data"), CacheSkillDatas);
	}

	return CacheSkillDatas;
}

const FSkillData* ATowerDefenceGameState::GetSkillData(const int32& SkillID)
{
	const TArray<FSkillData*>& SkillArray = GetSkillDataFormTable();
	for (const auto& Tmp : SkillArray)
	{
		if (SkillID == Tmp->ID)
		{
			return Tmp;
		}
	}
	return nullptr;
}

FGameInstanceDatas& ATowerDefenceGameState::GetGameData()
{
	
	return GetSaveData()->GameDatas;
}

const TArray<FCharacterData*>& ATowerDefenceGameState::GetTowerDataFormTable()
{
	
	if (!CacheTowerDatas.Num())
	{
		AITowerCharacterData->GetAllRows(TEXT("Character Data"), CacheTowerDatas);
	}

	return CacheTowerDatas;
}

const TArray<FCharacterData*>& ATowerDefenceGameState::GetMonsterDataFormTable()
{
	if (!CacheMonsterDatas.Num())
	{
		AIMonsterCharacterData->GetAllRows(TEXT("Character Data"), CacheMonsterDatas);
	}

	return CacheMonsterDatas;
}



//上述增删查改使用map
//遍历数组数据
// //.h中
// TArray<FCharacterData> CharacterData;
//for (auto& Tmp : CharacterData)
//if(Tmp.GUID == ID)
// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameCore/TowerDefencePlayerState.h"

//#include "Kismet/GameplayStatics.h"
//#include "Data/PlayerData.h"
//#include "TowersDefencePlayerController.h"
//#include "TowersDefenceGameInstance.h"
//#include "Data/CharacterData.h"

#include "Core/GameCore/TowerDefenceGameInstance.h"
#include "Business_process_2/FunctionUtils.h"
#include "UObject/ConstructorHelpers.h"		//获取数据库
#include "Kismet/GameplayStatics.h"			//读取 存储


//下面暂时没用
#include "Business_process_2\Macro.h"		//通用宏
#include "Data/Save/GameSaveData.h"			//存档
#include "Data/Save/GameSaveSlotList.h"		//存档位
#include "Character/Core/RuleOfTheCharacter.h" //生成角色
#include "Engine/DataTable.h"		//数据库


//ATowerDefencePlayerState::ATowerDefencePlayerState()
//{
//	static ConstructorHelpers::FObjectFinder<UDataTable> MyTable_PlayerSkill(TEXT("/Game/GameData/PlayerSkillData"));
//	PlayerSkillDataTable = MyTable_PlayerSkill.Object;
//
//
//}
//
//void ATowerDefencePlayerState::BeginPlay()
//{
//	Super::BeginPlay();
//}
//
//bool ATowerDefencePlayerState::SaveGameData(int32 SaveNumber)
//{
//	if (SaveData)
//	{
//		return UGameplayStatics::SaveGameToSlot(SaveData, FString::Printf(TEXT("PlayerData_%i"), SaveNumber), 0);
//	}
//
//	return false;
//}
//
//bool ATowerDefencePlayerState::ReadGameData(int32 SaveNumber)
//{
//	SaveData = Cast<UPlayerSaveData>(UGameplayStatics::LoadGameFromSlot(FString::Printf(TEXT("PlayerData_%i"), SaveNumber), 0));
//
//	return SaveData != nullptr;
//}
//
//const TArray<FPlayerSkillData*>& ATowerDefencePlayerState::GetPlayerSkillDataFormTable()
//{
//	if (!CachePlayerSkilDatas.Num())
//	{
//		PlayerSkillDataTable->GetAllRows(TEXT("Player Skill Data"), CachePlayerSkilDatas);
//	}
//
//	return CachePlayerSkilDatas;
//}
//
//const FPlayerSkillData* ATowerDefencePlayerState::GetPlayerSkillDataFormTable(const int32& PlayerSkillID)
//{
//	const TArray<FPlayerSkillData*>& InSkillDatas = GetPlayerSkillDataFormTable();
//	for (auto& Tmp : InSkillDatas)
//	{
//		if (Tmp->ID == PlayerSkillID)
//		{
//			return Tmp;
//		}
//	}
//
//	return NULL;
//}
//
//FPlayerSkillData* ATowerDefencePlayerState::GetPlayerSkillData(const FGuid& PlayerSkillGUID)
//{
//	if (GetSaveData()->PlayerSkillDatas.Contains(PlayerSkillGUID))
//	{
//		return &GetSaveData()->PlayerSkillDatas[PlayerSkillGUID];
//	}
//
//	return nullptr;
//}
//
//bool ATowerDefencePlayerState::IsVerificationSkill(const FGuid& SlotID)
//{
//	if (FPlayerSkillData* InData = GetPlayerSkillData(SlotID))
//	{
//		if (InData->IsValid() && InData->SkillNumber > 0 && InData->GetCDPercent() <= 0.f)
//		{
//			return true;
//		}
//	}
//
//	return false;
//}
//
//void ATowerDefencePlayerState::UsePlayerSkill(const FGuid& SlotID)
//{
//	if (FPlayerSkillData* InData = GetPlayerSkillData(SlotID))
//	{
//		if (InData->IsValid())
//		{
//			InData->SkillNumber--;
//			InData->ResetCD();
//			//通知客户端更新添加的UI
//			StoneDefenceUtils::CallUpdateAllClient(GetWorld(), [&](ATowersDefencePlayerController* MyPlayerController)
//				{
//					MyPlayerController->SpawnPlayerSkill_Client(InData->ID);
//				});
//		}
//	}
//}
//
//void ATowerDefencePlayerState::AddPlayerSkill(const FGuid* Guid, int32 SkillID)
//{
//	GetSaveData()->AddPlayerSkill(GetWorld(), Guid, SkillID);
//}

FBuildingTower& ATowerDefencePlayerState::GetBuildingTower(const FGuid& ID)
{
	if (GetSaveData()->BuildingTowers.Contains(ID))
	{
		return GetSaveData()->BuildingTowers[ID];
	}

	//SD_print(Error, "The current [%s] is invalid", *ID.ToString());
	return BuildingTowerNULL;
}



FPlayerData& ATowerDefencePlayerState::GetPlayerData()
{
	return GetSaveData()->PlayerData;
}

const FBuildingTower& ATowerDefencePlayerState::AddBuildingTower(const FGuid& ID, const FBuildingTower& Data)
{
	return GetSaveData()->BuildingTowers.Add(ID, Data);
}

const TArray<const FGuid*> ATowerDefencePlayerState::GetBuildingTowersID()
{
	TArray<const FGuid*> TowersID;
	for (const auto& Tmp : GetSaveData()->BuildingTowers)
	{
		TowersID.Add(&Tmp.Key);
	}

	return TowersID;
}

void ATowerDefencePlayerState::RequestInventorySlotSwap(const FGuid& A, const FGuid& B)
{
	FBuildingTower& ASlot = GetBuildingTower(A);
	FBuildingTower& BSlot = GetBuildingTower(B);

	if (ASlot.IsValid()) //交换
	{
		FBuildingTower TmpSlot = ASlot;
		ASlot = BSlot;
		BSlot = TmpSlot;
	}
	else //移动
	{
		ASlot = BSlot;
		BSlot.Init();
	}
}

//void ATowerDefencePlayerState::RequestInventorySlotSwap(const FGuid& A, const FGuid& B)
//{
//	FBuildingTower& ASlot = GetBuildingTower(A);
//	FBuildingTower& BSlot = GetBuildingTower(B);
//
//	if (ASlot.IsValid()) //交换
//	{
//		FBuildingTower TmpSlot = ASlot;
//		ASlot = BSlot;
//		BSlot = TmpSlot;
//	}
//	else //移动
//	{
//		ASlot = BSlot;
//		BSlot.Init();
//	}
//}

FBuildingTower& ATowerDefencePlayerState::GetBuildingTowerNULL()
{
	return BuildingTowerNULL;
}

UPlayerSaveData* ATowerDefencePlayerState::GetSaveData()
{
	if (!SaveData)
	{
		if (UTowerDefenceGameInstance* InGameInstance = GetWorld()->GetGameInstance<UTowerDefenceGameInstance>())
		{
			SaveData = FunctionUtils::GetSave<UPlayerSaveData>(
				GetWorld(),
				TEXT("PlayerData_%i"),
				InGameInstance->GetCurrentSaveSlotNumber(),
				InGameInstance->GetGameType());
		}
	}

	return SaveData;
}

void ATowerDefencePlayerState::TowersPrepareBuildingNumber(const FGuid& InventoryGUID)
{

	FBuildingTower& BT = GetBuildingTower(InventoryGUID);
	if (BT.IsValid()) //服务器验证 防止作弊
	{

		if (/*BT.NeedGold <= GetPlayerData().GameGold*/1)
		{
			BT.TowersPerpareBuildingNumber++;
			GetPlayerData().GameGold -= BT.NeedGold;

			if (BT.CurrentConstrictionTowersCD <= 0)
			{
				BT.ResetCD();
			}
		}
	}

}

void ATowerDefencePlayerState::SetTowersDragICONState(const FGuid& InventoryGUID, bool bDragICON)
{
	FBuildingTower& BT = GetBuildingTower(InventoryGUID);
	BT.bDragICON = bDragICON;
}

void ATowerDefencePlayerState::TowersConstructionNumber(const FGuid& InventoryGUID, int32 InValue)
{
	FBuildingTower& BT = GetBuildingTower(InventoryGUID);
	if (BT.IsValid()) //服务器验证 防止作弊
	{
		BT.TowersConstructionNumber += InValue;
	}
}

//FPlayerSkillData* ATowerDefencePlayerState::GetSkillDatas(const FGuid& SkillGuid)
//{
//	if (GetSaveData()->PlayerSkillDatas.Contains(SkillGuid))
//	{
//		return &GetSaveData()->PlayerSkillDatas[SkillGuid];
//	}
//
//	SD_print(Error, "The current [%s] is invalid", *SkillGuid.ToString());
//	return nullptr;
//}
//
//const TArray<const FGuid*> ATowerDefencePlayerState::GetSkillDatasID()
//{
//	TArray<const FGuid*> SkillIDs;
//	for (const auto& Tmp : GetSaveData()->PlayerSkillDatas)
//	{
//		SkillIDs.Add(&Tmp.Key);
//	}
//
//	return SkillIDs;
//}


//void ATowerDefencePlayerState::SetTowersDragICOState(const FGuid& InventoryGUID, bool bDragICON)
//{
//	FBuildingTower& BT = GetBuildingTower(InventoryGUID);
//	BT.bDragICON = bDragICON;
//}
//
//void ATowerDefencePlayerState::TowersConstructionNumber(const FGuid& InventoryGUID, int32 InValue /*= INDEX_NONE*/)
//{
//	FBuildingTower& BT = GetBuildingTower(InventoryGUID);
//	if (BT.IsValid()) //服务器验证 防止作弊
//	{
//		BT.TowersConstructionNumber += InValue;
//	}
//}


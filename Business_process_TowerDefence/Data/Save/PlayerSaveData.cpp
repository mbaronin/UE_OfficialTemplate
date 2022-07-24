// Fill out your copyright notice in the Description page of Project Settings.

#include "Data\Save\PlayerSaveData.h"

#include "Core/GameCore/TowerDefenceGameState.h"
#include "Data/Core/CharacterData.h"
//#include "Core/GameCore/TowersDefencePlayerState.h"
//#include "Core/GameCore/TowersDefencePlayerController.h"
//#include "StoneDefenceUtils.h"

void UPlayerSaveData::InitSaveGame(UWorld *InWorld)
{
	if(ATowerDefenceGameState *InGameState = InWorld->GetGameState<ATowerDefenceGameState>())
	{
		const TArray<FCharacterData*> &Datas = InGameState->GetTowerDataFormTable();

		//��Ʒ������slot 
		for (int32 i = 0; i < 21; i++)
		{
			FBuildingTower BuildingTower;
			if (Datas.IsValidIndex(i))
			{
				BuildingTower.TowerID = Datas[i]->ID;
				BuildingTower.NeedGold = Datas[i]->Glod;
				BuildingTower.MaxConstructionTowersCD = Datas[i]->CD;
				BuildingTower.ICON = Datas[i]->Icon.LoadSynchronous();
			}

			
			BuildingTowers.Add(FGuid::NewGuid(), BuildingTower);
		}

		////���ܸ�ֵ �����ڷ�����
		//for (int32 i = 0; i < 10; i++)
		//{
		//	FGuid ID = FGuid::NewGuid();
		//	if (PlayerData.SkillIDs.IsValidIndex(i))
		//	{
		//		AddPlayerSkill(InWorld,&ID,PlayerData.SkillIDs[i]);
		//	}
		//	else
		//	{
		//		PlayerSkillDatas.Add(ID, FPlayerSkillData());
		//	}
		//}
	}	
}

void UPlayerSaveData::AddPlayerSkill(UWorld *InWorld, const FGuid *Guid, int32 SkillID)
{
	//if (ATowersDefencePlayerState *InPlayerState = InWorld->GetFirstPlayerController()->GetPlayerState<ATowersDefencePlayerState>())
	//{
	//	if (const FPlayerSkillData *FSkill = InPlayerState->GetPlayerSkillDataFormTable(SkillID))
	//	{	
	//		if (PlayerSkillDatas.Contains(*Guid))
	//		{
	//			PlayerSkillDatas[*Guid] = *FSkill;
	//		}
	//		else
	//		{
	//			PlayerSkillDatas.Add(*Guid, *FSkill);
	//		}

	//		//֪ͨ�ͻ��˸�����ӵ�UI
	//		StoneDefenceUtils::CallUpdateAllClient(InWorld, [&](ATowersDefencePlayerController *MyPlayerController)
	//		{
	//			MyPlayerController->UpdatePlayerSkill_Client(*Guid, false);
	//		});
	//	}
	//}
}


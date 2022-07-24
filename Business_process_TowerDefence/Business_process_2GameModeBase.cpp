// Copyright Epic Games, Inc. All Rights Reserved.


#include "Business_process_2GameModeBase.h"

#include "Core/GameCore/TowerDefenceGameState.h"
#include "Core/GameCore/TowerDefencePlayerController.h"
#include "Core/GameCore/TowerDefenceGameCamera.h"
#include "Core/GameCore/TowerDefencePlayerState.h"
#include "UI/GameUI/Core/RuleofTheHUD.h"

#include "Character/Core/RuleOfTheCharacter.h"

#include "Engine/DataTable.h"		//数据库
#include "Business_process_2\FunctionUtils.h"


#include "Character/CharacterCore/Monster.h"
#include "Character/CharacterCore/Towers.h"

ABusiness_process_2GameModeBase::ABusiness_process_2GameModeBase()
{
	GameStateClass = ATowerDefenceGameState::StaticClass();
	PlayerControllerClass = ATowerDefencePlayerController::StaticClass();
	DefaultPawnClass = ATowerDefenceGameCamera::StaticClass();
	PlayerStateClass = ATowerDefencePlayerState::StaticClass();
	HUDClass = ARuleofTheHUD::StaticClass();
	
	PrimaryActorTick.bCanEverTick = true;

}

void ABusiness_process_2GameModeBase::BeginPlay()
{
	//if (UTowersDefenceGameInstance* InGameInstance = GetWorld()->GetGameInstance<UTowersDefenceGameInstance>())
	//{
	//	if (ATowersDefenceGameState* InGameState = GetGameState<ATowersDefenceGameState>())
	//	{
	//		if (InGameInstance->GetCurrentSaveSlotNumber() == INDEX_NONE &&
	//			InGameInstance->GetGameType() == EGameSaveType::NONE)
	//		{
	//			InitData();
	//		}
	//		else //通过存档读取的数据
	//		{
	//			//从存档中读取数据
	//			InitDataFormArchives();

	//			//清除存档痕迹
	//			InGameInstance->ClearSaveMark();

	//			//还原我们场景中的角色
	//			for (auto& Tmp : InGameState->GetSaveData()->CharacterDatas)
	//			{
	//				if (Tmp.Value.Team == ETeam::RED)
	//				{
	//					SpawnTowers(Tmp.Value.ID, Tmp.Value.Location, Tmp.Value.Rotator, Tmp.Key);
	//				}
	//				else
	//				{
	//					SpawnMonster(Tmp.Value.ID, Tmp.Value.Location, Tmp.Value.Rotator, Tmp.Key);
	//				}
	//			}
	//		}
	//	}
	//}
}

void ABusiness_process_2GameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	////更新玩家的数据
	//UpdatePlayerData(DeltaSeconds);

	//更新 数据GameData
	UpdateGameData(DeltaSeconds);

	////更新生成怪物
	//UpdateMonstersRule(DeltaSeconds);

	////更新技能
	//UpdateSkill(DeltaSeconds);

	//更新装备栏
	UpdateInventory(DeltaSeconds);

	////更新玩家的技能
	//UpdatePlayerSkill(DeltaSeconds);
	
}


ATowers* ABusiness_process_2GameModeBase::SpawnTowers(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotator)
{
	return SpawnCharacter<ATowers>(CharacterID, CharacterLevel, GetGameState<ATowerDefenceGameState>()->AITowerCharacterData, Location, Rotator);
}

//ATowers* ABusiness_process_2GameModeBase::SpawnTowers(int32 CharacterID, const FVector& Location, const FRotator& Rotator, const FGuid& InCharacterGuid /*= FGuid()*/)
//{
//	return SpawnCharacter<ATowers>(CharacterID, 1, GetGameState<ATowerDefenceGameState>()->AITowerCharacterData, Location, Rotator, InCharacterGuid);
//}

AMonster* ABusiness_process_2GameModeBase::SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotator)
{
	return SpawnCharacter<AMonster>(CharacterID, CharacterLevel, GetGameState<ATowerDefenceGameState>()->AIMonsterCharacterData, Location, Rotator);
}

//AMonster* ABusiness_process_2GameModeBase::SpawnMonster(int32 CharacterID, const FVector& Location, const FRotator& Rotator, const FGuid& InCharacterGuid /*= FGuid()*/)
//{
//	return SpawnCharacter<AMonster>(CharacterID, 1, GetGameState<ATowerDefenceGameState>()->AIMonsterCharacterData, Location, Rotator, InCharacterGuid);
//}





ARuleOfTheCharacter* ABusiness_process_2GameModeBase::SpawnCharacter(
	int32 CharacterID,
	int32 CharacterLevel,
	UDataTable* InCharacterData,
	const FVector& Location,
	const FRotator& Rotator,
	const FGuid& InCharacterGuid)
{
	ARuleOfTheCharacter* InCharacter = nullptr;

	if (ATowerDefenceGameState* InGameState = GetGameState<ATowerDefenceGameState>())
	{
		if (InCharacterData)
		{
			//临时函数
			//遍历 CharacterData数组 //找到int32 ID 相同的 CharacterData 返回			
			TArray<FCharacterData*> Datas;
			InCharacterData->GetAllRows(TEXT("Character Data"), Datas);
			auto GetCharacterData = [&](int32 ID) ->const FCharacterData*
			{
				for (auto& Tmp : Datas)
				{
					if (Tmp->ID == ID)
					{
						return Tmp;
					}
				}
				return nullptr;
			};

			if (const FCharacterData* CharacterData = GetCharacterData(CharacterID))
			{
				UClass* NewClass = CharacterData->CharacterBlueprintKey.LoadSynchronous();
				if (GetWorld() && NewClass)
				{
					FTransform Transform;
					Transform.SetLocation(Location);
					Transform.SetRotation(FQuat(Rotator));
					if (ARuleOfTheCharacter* RuleOfTheCharacter = GetWorld()->SpawnActor<ARuleOfTheCharacter>(NewClass, Location, Rotator))
					{
						//GetWorld()->SpawnActor<ARuleOfTheCharacter>(NewClass, Location, Rotator))
						//GetWorld()->SpawnActorDeferred<ARuleOfTheCharacter>(NewClass, Transform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn)
						if (InCharacterGuid == FGuid())//新出来的对象
						{
							RuleOfTheCharacter->GUID = FGuid::NewGuid();

							if (FCharacterData* CharacterDataInst = InGameState->AddCharacterData(RuleOfTheCharacter->GUID, *CharacterData))
							{
								CharacterDataInst->UpdateHealth();

								if (CharacterLevel > 1)
								{
									for (int32 i = 0; i < CharacterLevel; i++)
									{
										CharacterDataInst->UpdateLevel();
									}
								}

								////初始化被动技能
								//RuleOfTheCharacter->InitSkill();

								////注册相应的队伍
								//RuleOfTheCharacter->RegisterTeam();
							}
						}
						else //还原的对象
						{
							RuleOfTheCharacter->GUID = InCharacterGuid;
						}

						InCharacter = RuleOfTheCharacter;
					}
				}
			}
		}
	}

	return InCharacter;
}




void CallUpdateAllClient(UWorld* World, TFunction<void(ATowerDefencePlayerController* MyPlayerController)> InImplement)
{
	if (World)
	{
		for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
		{
			if (ATowerDefencePlayerController* MyPlayerController = Cast<ATowerDefencePlayerController>(It->Get()))
			{
				InImplement(MyPlayerController);
			}
		}
	}
}




void ABusiness_process_2GameModeBase::UpdateGameData(float DeltaSeconds)
{

	if (ATowerDefenceGameState* InGameState = GetGameState<ATowerDefenceGameState>())
	{
		//倒计时
		if (InGameState->GetGameData().GameCount <= 0.f)
		{
			InGameState->GetGameData().bGameOver = true;
		}
		else
		{
			InGameState->GetGameData().GameCount -= DeltaSeconds;
		}

		//遍历所有Tower 为0结束游戏
		int32 TowersNum = 0;
		TArray<ARuleOfTheCharacter*> InTowers;
		FunctionUtils::GetAllActor<ATowers>(GetWorld(), InTowers);
		for (ARuleOfTheCharacter* Tower : InTowers)
		{
			if (Tower->IsActive())
			{
				TowersNum++;
			}
		}
		if (TowersNum == 0)
		{
			InGameState->GetGameData().bGameOver = true;
		}

	}


}

void ABusiness_process_2GameModeBase::UpdateInventory(float DeltaSeconds)
{
	if (ATowerDefenceGameState* InGameState = GetGameState<ATowerDefenceGameState>())
	{
		FunctionUtils::CallUpdateAllClient(GetWorld(), [&](ATowerDefencePlayerController* MyPlayerController)
			{
				if (ATowerDefencePlayerState* InPlayerState = MyPlayerController->GetPlayerState<ATowerDefencePlayerState>())
				{
					for (auto& Tmp : InPlayerState->GetSaveData()->BuildingTowers)
					{
						if (Tmp.Value.IsValid())
						{
							if (!Tmp.Value.bLockCD)
							{
								if (!Tmp.Value.bDragICON)
								{
									if (Tmp.Value.CurrentConstrictionTowersCD > 0)
									{
										Tmp.Value.CurrentConstrictionTowersCD -= DeltaSeconds;
										Tmp.Value.bCallUpdateTowersInfo = true;

										//通知客户端更新我们的装备CD
										FunctionUtils::CallUpdateAllClient(GetWorld(), [&](ATowerDefencePlayerController* MyPlayerController)
											{
												MyPlayerController->UpdateInventory_Client(Tmp.Key, true);
											});
									}
									else if (Tmp.Value.bCallUpdateTowersInfo)
									{
										Tmp.Value.bCallUpdateTowersInfo = false;
										//准备构建的塔
										Tmp.Value.TowersPerpareBuildingNumber--;
										Tmp.Value.TowersConstructionNumber++;

										//通知客户端更新我们的装备CD
										FunctionUtils::CallUpdateAllClient(
											GetWorld(), 
											[&](ATowerDefencePlayerController* MyPlayerController)
											{MyPlayerController->UpdateInventory_Client(Tmp.Key, false);}
										);

										if (/*Tmp.Value.TowersPerpareBuildingNumber >*/ 0)
										{
											GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("this is  gamemode end resetCD!"));
											Tmp.Value.ResetCD();
										}
									}
								}
							}
						}
					}
				}
			}
		);//第一个Fuction 结束
	}

}









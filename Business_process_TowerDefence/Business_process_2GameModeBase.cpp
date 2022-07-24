// Copyright Epic Games, Inc. All Rights Reserved.


#include "Business_process_2GameModeBase.h"

#include "Core/GameCore/TowerDefenceGameState.h"
#include "Core/GameCore/TowerDefencePlayerController.h"
#include "Core/GameCore/TowerDefenceGameCamera.h"
#include "Core/GameCore/TowerDefencePlayerState.h"
#include "UI/GameUI/Core/RuleofTheHUD.h"

#include "Character/Core/RuleOfTheCharacter.h"

#include "Engine/DataTable.h"		//���ݿ�
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
	//		else //ͨ���浵��ȡ������
	//		{
	//			//�Ӵ浵�ж�ȡ����
	//			InitDataFormArchives();

	//			//����浵�ۼ�
	//			InGameInstance->ClearSaveMark();

	//			//��ԭ���ǳ����еĽ�ɫ
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

	////������ҵ�����
	//UpdatePlayerData(DeltaSeconds);

	//���� ����GameData
	UpdateGameData(DeltaSeconds);

	////�������ɹ���
	//UpdateMonstersRule(DeltaSeconds);

	////���¼���
	//UpdateSkill(DeltaSeconds);

	//����װ����
	UpdateInventory(DeltaSeconds);

	////������ҵļ���
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
			//��ʱ����
			//���� CharacterData���� //�ҵ�int32 ID ��ͬ�� CharacterData ����			
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
						if (InCharacterGuid == FGuid())//�³����Ķ���
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

								////��ʼ����������
								//RuleOfTheCharacter->InitSkill();

								////ע����Ӧ�Ķ���
								//RuleOfTheCharacter->RegisterTeam();
							}
						}
						else //��ԭ�Ķ���
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
		//����ʱ
		if (InGameState->GetGameData().GameCount <= 0.f)
		{
			InGameState->GetGameData().bGameOver = true;
		}
		else
		{
			InGameState->GetGameData().GameCount -= DeltaSeconds;
		}

		//��������Tower Ϊ0������Ϸ
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

										//֪ͨ�ͻ��˸������ǵ�װ��CD
										FunctionUtils::CallUpdateAllClient(GetWorld(), [&](ATowerDefencePlayerController* MyPlayerController)
											{
												MyPlayerController->UpdateInventory_Client(Tmp.Key, true);
											});
									}
									else if (Tmp.Value.bCallUpdateTowersInfo)
									{
										Tmp.Value.bCallUpdateTowersInfo = false;
										//׼����������
										Tmp.Value.TowersPerpareBuildingNumber--;
										Tmp.Value.TowersConstructionNumber++;

										//֪ͨ�ͻ��˸������ǵ�װ��CD
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
		);//��һ��Fuction ����
	}

}









#include "Data\Core\GameData.h"





FGameInstanceDatas::FGameInstanceDatas()
{
	Init();
}

void FGameInstanceDatas::Init()
{
	MaxStagesAreMonsters = 4;
	MaxMonsters = 20;
	GameDifficulty = 0;
	bAllMainTowerDie = false;
	bGameOver = false;
	bCurrentLevelMissionSuccess = false;
	CurrentLevel = INDEX_NONE;
	TimeInterval = 4.f;
	GameCount = 1000;
	MaxGameCount = 0;
	GoldGrowthTime = 1.f;
	GoldGrowthMaxTime = 1.5f;
	KillMonstersNumber = 0;
	KillMonsterBossNumber = 0;
	TowersDeathNumber = 0;
	MainTowersDeathNumber = 0;
	CurrentSpawnMosnterTime = 0.0f;
}

int32 FGameInstanceDatas::GetSurplusMonsters()
{
	int32 InSurplus = 0;
	for (auto &Tmp : PerNumberOfMonsters)
	{
		InSurplus += Tmp;
	}

	return InSurplus;
	return 0;
}

float FGameInstanceDatas::GetPerOfRemMonsters()
{
	if (MaxMonsters != 0)
	{
		return (float)GetSurplusMonsters() / (float)MaxMonsters;
	}

	return 0.f;
}

void FGameInstanceDatas::ResetSpawnMosnterTime()
{
	CurrentSpawnMosnterTime = 0.0f;
}

void FGameInstanceDatas::StageDecision()
{
	/*int32 CurrentStagesAreMonsters = PerNumberOfMonsters.Num() - 1;
	if (PerNumberOfMonsters.Num())
	{
		if (PerNumberOfMonsters[CurrentStagesAreMonsters] > 0)
		{
			PerNumberOfMonsters[CurrentStagesAreMonsters]--;
		}
		else
		{
			PerNumberOfMonsters.RemoveAt(CurrentStagesAreMonsters);
			CallClientUpdate.ExecuteIfBound(CurrentStagesAreMonsters);
		}
	}
	else
	{
		bCurrentLevelMissionSuccess = true;
	}*/
}

void FGameInstanceDatas::AssignedMonsterAmount()
{
	////���ٵĹ���
	//int32 CurrentMonsterNumber = MaxMonsters;

	////���׶�
	//int32 CurrentStagesNumber = MaxStagesAreMonsters;

	////ÿ�׶ε�����
	//int32 CurrentAssignedNum = 0;

	//if (CurrentMonsterNumber > 1)
	//{
	//	for (int32 i = 0; i < MaxStagesAreMonsters; i++) //ÿ�׶�
	//	{
	//		//ÿ�׶ε�ƽ��ֵ
	//		float StagesNumber = (float)CurrentMonsterNumber / (float)CurrentStagesNumber;
	//	
	//		//��ȥ�ý׶�
	//		CurrentStagesNumber--;
	//		if (CurrentStagesNumber > 0)
	//		{	
	//			//����׶Σ���ƽ��ֵһ�㵽ƽ��ֵ����
	//			CurrentAssignedNum = FMath::RandRange(StagesNumber / 6, StagesNumber);
	//		}
	//		else
	//		{
	//			CurrentAssignedNum = StagesNumber;
	//		}

	//		PerNumberOfMonsters.Add(CurrentAssignedNum);

	//		//��ȥ���������
	//		CurrentMonsterNumber -= CurrentAssignedNum;
	//	}
	//}
	//else
	//{
	//	PerNumberOfMonsters.Add(CurrentAssignedNum);
	//}

	////��ʼ����
	//CallClientUpdate.ExecuteIfBound(MaxStagesAreMonsters);
}






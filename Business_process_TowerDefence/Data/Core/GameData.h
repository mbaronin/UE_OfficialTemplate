#pragma once

#include "CoreMinimal.h"
#include "Business_process_2\EnumType.h"
#include "GameData.generated.h"

 
USTRUCT()
struct FGameInstanceDatas
{
	GENERATED_USTRUCT_BODY()

	FGameInstanceDatas();

	void Init();

	FSimpleOneInt32Delegate CallClientUpdate;

	//bool IsValid();

	//�ùؿ��ڴ��������ٹ�������
	UPROPERTY(SaveGame)
	int32 MaxMonsters;

	//�ж��ٲ�����
	UPROPERTY(SaveGame)
	int32 MaxStagesAreMonsters;

	//ÿ�����ﵱǰ���� �����Ƕ�̬
	UPROPERTY(SaveGame)
	TArray<int32> PerNumberOfMonsters;

	//��Ϸ�Ѷ�
	UPROPERTY(SaveGame)
	uint8 GameDifficulty;

	//������е���������,��ֵΪtrue,���ҽ�ֹ�����κν���
	UPROPERTY(SaveGame)
	uint8 bAllMainTowerDie : 1;

	//����������,��Ϸ����
	UPROPERTY(Transient)
	uint8 bGameOver : 1;

	UPROPERTY(Transient)
	uint8 bCurrentLevelMissionSuccess : 1;

	//��ǰ�ؿ�
	UPROPERTY(SaveGame)
	int32 CurrentLevel;

	//ʱ�������������һ�ι��
	UPROPERTY(SaveGame)
	float TimeInterval;

	//���ɹ����ʱ���¼
	UPROPERTY(SaveGame)
	float CurrentSpawnMosnterTime;

	//��ʱ��ĵ���ʱ
	UPROPERTY(SaveGame)
	float GameCount;

	//�����ʱ��ĵ���ʱ
	UPROPERTY(SaveGame)
	float MaxGameCount;

	//�ƽ������ʱ��
	UPROPERTY(Transient)
	float GoldGrowthTime;

	//���ƽ������ʱ��
	UPROPERTY(Transient)
	float GoldGrowthMaxTime;

	//ɱ������������
	UPROPERTY(SaveGame)
	int32 KillMonstersNumber;

	//ɱ��Boss����
	UPROPERTY(SaveGame)
	int32 KillMonsterBossNumber;

	//����������
	UPROPERTY(SaveGame)
	int32 TowersDeathNumber;

	//����������
	UPROPERTY(SaveGame)
	int32 MainTowersDeathNumber;

	int32 GetSurplusMonsters();

	float GetPerOfRemMonsters();

	void ResetSpawnMosnterTime();

	//ÿ���׶ν��м���ж�
	void StageDecision();

	//���������ݶȣ��������ٱ��
	void AssignedMonsterAmount();

	FORCEINLINE bool IsAllowSpawnMosnter() { return CurrentSpawnMosnterTime >= TimeInterval; }
};

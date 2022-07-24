#pragma once

#include "CoreMinimal.h"
#include "Business_process_2\EnumType.h"
//#include "Data/PlayerSkillData.h"

#include "PlayerData.generated.h"


USTRUCT()
struct FPlayerData
{
	GENERATED_USTRUCT_BODY()

	FPlayerData();

	void Init();

	bool IsValid();

	//���ID
	UPROPERTY(SaveGame)
	int32 PlayID;

	//�������
	UPROPERTY(SaveGame)
	FName PlayName;

	//����
	UPROPERTY(SaveGame)
	TEnumAsByte<ETeam> Team;

	//����˻�
	UPROPERTY(SaveGame)
	FString Account;

	//��Ϸ���
	UPROPERTY(SaveGame)
	int32 GameGold;

	//��ʯ ��Ҫ����
	UPROPERTY(SaveGame)
	int32 Diamonds;

	//ͭ�� 
	UPROPERTY(SaveGame)
	int32 Copper;

	UPROPERTY(SaveGame)
	float GameGoldTime;
	
	UPROPERTY(SaveGame)
	float MaxGameGoldTime;

	//���ӵ�еļ���
	UPROPERTY(SaveGame)
	TArray<int32> SkillIDs;

	bool IsAllowIncrease();
};
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "BuildingTowerData.generated.h"

class UTexture2D;


USTRUCT()
struct FBuildingTower
{
	GENERATED_BODY()

	UPROPERTY(SaveGame)
		int32 TowerID;

	//��Ҫ�����ѽ��
	UPROPERTY(SaveGame)
		int32 NeedGold;

	//׼���׶�����������
	UPROPERTY(SaveGame)
		int32 TowersPerpareBuildingNumber;

	//���Ѿ���������
	UPROPERTY(SaveGame)
		int32 TowersConstructionNumber;

	//��ǰ�������CD
	UPROPERTY(SaveGame)
		float MaxConstructionTowersCD;

	//��ǰ����������CD
	UPROPERTY(SaveGame)
		float CurrentConstrictionTowersCD;

	//��ΪICONָ��
	UPROPERTY(SaveGame)
		UTexture2D* ICON;

	//�Ƿ���קͼ��
	UPROPERTY(SaveGame)
		bool bDragICON;

	//��
	UPROPERTY(SaveGame)
		bool bLockCD;

	UPROPERTY(SaveGame)
		bool bCallUpdateTowersInfo;

public:
	FBuildingTower();

	void Init();

	float GetTowerConstructionTimePercentage();

	bool IsValid();

	void ResetCD();
};

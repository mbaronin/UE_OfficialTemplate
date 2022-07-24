
#include "Data/Core/BuildingTowerData.h"

FBuildingTower::FBuildingTower()
{
	Init();
}

void FBuildingTower::Init()
{
	TowerID = INDEX_NONE;
	NeedGold = INDEX_NONE;
	TowersPerpareBuildingNumber = 0.0f;
	TowersConstructionNumber = 0.0f;
	MaxConstructionTowersCD = 0.0f;;
	CurrentConstrictionTowersCD = 0.0f;;
	ICON = NULL;
	bDragICON = false;
	bLockCD = false;
	bCallUpdateTowersInfo = false;
}

//返回技能CD百分比
float FBuildingTower::GetTowerConstructionTimePercentage()
{
	return MaxConstructionTowersCD > 0.f ? CurrentConstrictionTowersCD / MaxConstructionTowersCD : 0.f;
}

bool FBuildingTower::IsValid()
{
	return TowerID != INDEX_NONE;
}

void FBuildingTower::ResetCD()
{
	CurrentConstrictionTowersCD = MaxConstructionTowersCD;
}



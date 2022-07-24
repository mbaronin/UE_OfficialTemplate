#include "Global/UI_Datas.h"
#include "Character/Core/RuleOfTheCharacter.h"

int32 PlayerSkillNumber = 0;

FGuid TmpTowerGUID;
AActor * TowerPreview = nullptr;
bool bLockGUID = false;


ARuleOfTheCharacter *ClickedTargetTower = nullptr;
ARuleOfTheCharacter *ClickedTargetMonster = nullptr;
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class ARuleOfTheCharacter;




extern int32 PlayerSkillNumber;

//光标进入InventorySlot 获取的GUID
extern FGuid TmpTowerGUID;

//Spawn塔预览网格体
extern AActor *TowerPreview;

//光标点击InventorySlot 锁定GUID
extern bool bLockGUID;


//点击 事件 目标
extern ARuleOfTheCharacter *ClickedTargetTower;
extern ARuleOfTheCharacter *ClickedTargetMonster;
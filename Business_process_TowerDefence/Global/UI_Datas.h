// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class ARuleOfTheCharacter;




extern int32 PlayerSkillNumber;

//������InventorySlot ��ȡ��GUID
extern FGuid TmpTowerGUID;

//Spawn��Ԥ��������
extern AActor *TowerPreview;

//�����InventorySlot ����GUID
extern bool bLockGUID;


//��� �¼� Ŀ��
extern ARuleOfTheCharacter *ClickedTargetTower;
extern ARuleOfTheCharacter *ClickedTargetMonster;
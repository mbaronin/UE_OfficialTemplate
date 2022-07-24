// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TDGameResources.generated.h"

/**
 * 定义类型的文件
 */
UCLASS()
class BUSINESS_PROCESS_2_API UTDGameResources : public UObject
{
	GENERATED_BODY()
	
};



////角色类型
//UENUM(BlueprintType)//暴露给蓝图
//enum class ECharacterType :uint8
//{
//	TOWER,
//	MAIN_TOWER,
//	MONSTER,
//	BOSS_MONSTER,
//	NONE,
//};


////子弹类型
//UENUM(BlueprintType)
//enum class EBulletType :uint8
//{
//	BULLET_NONE,			//不产生任何效果
//
//	BULLET_DIRECT_LINE,		//无障碍直线攻击，穿透
//	BULLET_LINE,			//非跟踪类型，类子弹；
//	BULLET_TRACK_LINE,		//跟踪类型
//	BULLET_TRACK_LINE_SP,	//跟踪类型
//	BULLET_RANGE_THROW,		//范围伤害，丢手雷；
//	BULLET_RANGE,			//范围伤害，类似自爆；
//	BULLET_CHAIN,			//链条类型，持续伤害类型;
//};



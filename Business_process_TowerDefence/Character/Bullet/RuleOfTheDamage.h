// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "RuleOfTheDamage.generated.h"

/**
 * 
 */
UCLASS()
class BUSINESS_PROCESS_2_API URuleOfTheDamage : public UDamageType
{
	GENERATED_BODY()

public:
	const struct FSkillData* SkillData = nullptr;
};

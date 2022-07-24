// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "AIController.h"
#include "Character/AIController/RuleOfTheAIController.h"
#include "MonsterAIController.generated.h"

class ARuleOfTheCharacter;

/**
 * 
 */
UCLASS()
class BUSINESS_PROCESS_2_API AMonsterAIController : public ARuleOfTheAIController//AAIController
{
	GENERATED_BODY()
	
public:
	virtual AActor* FindTarget();
	virtual void AttackTarget(ARuleOfTheCharacter* InTarget);

//public:

//	TWeakObjectPtr<ARuleOfTheCharacter> Target; 


	//寻找最近塔(目标)(写在函数库里了)
	//ARuleOfTheCharacter* FindTargetRecently(const TArray<ARuleOfTheCharacter*>& InCharacters, const FVector& Loc);

};

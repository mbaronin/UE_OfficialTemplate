// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "AIController.h"
#include "Character/AIController/RuleOfTheAIController.h"
#include "TowersAIController.generated.h"

class ARuleOfTheCharacter;
/**
 * 
 */
UCLASS()
class BUSINESS_PROCESS_2_API ATowersAIController : public ARuleOfTheAIController//AAIController
{
	GENERATED_BODY()
	

public:
	ATowersAIController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

protected:

	void BTService_FindTarget();

	virtual void AttackTarget(ARuleOfTheCharacter* InTarget);

protected:

	//π÷ŒÔ∫œºØ
	UPROPERTY()
		TArray<ARuleOfTheCharacter*> TArrayMonsters;

	float Heartbeat;

//public:
//	TWeakObjectPtr<ARuleOfTheCharacter> Target;
};

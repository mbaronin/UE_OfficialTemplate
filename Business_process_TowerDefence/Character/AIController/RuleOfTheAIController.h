// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RuleOfTheAIController.generated.h"

class ARuleOfTheCharacter;
/**
 * 
 */
UCLASS()
class BUSINESS_PROCESS_2_API ARuleOfTheAIController : public AAIController
{
	GENERATED_BODY()
public:

	virtual AActor* FindTarget() { return nullptr; };
	virtual void AttackTarget(ARuleOfTheCharacter* InTarget) {};

	UFUNCTION(Blueprintable, BlueprintPure, Category = "Test")
		ARuleOfTheCharacter* GetTarget();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//	//��ָ�� (�����ֶ�����)
	TWeakObjectPtr<ARuleOfTheCharacter> Target;
};

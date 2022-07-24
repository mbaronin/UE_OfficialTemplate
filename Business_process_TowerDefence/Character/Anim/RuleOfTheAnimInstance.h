// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RuleOfTheAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BUSINESS_PROCESS_2_API URuleOfTheAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	URuleOfTheAnimInstance();

	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float Deltaseconds);


protected:
	bool IsDelayUpdate(float Deltaseconds);

public:
	//±©Â¶¸øÀ¶Í¼
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute")
		bool IsDeath;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute")
		bool IsAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute")
		float Speed;
	//Ðý×ª
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute")
		FRotator CharacterRotator;

private:

	float CurrentTime;
	bool bDelayTime;

};

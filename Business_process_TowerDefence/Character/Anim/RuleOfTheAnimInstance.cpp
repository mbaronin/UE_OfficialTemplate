// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Anim/RuleOfTheAnimInstance.h"
#include "Character/Core/RuleOfTheCharacter.h"

URuleOfTheAnimInstance::URuleOfTheAnimInstance()
	:IsDeath(false)
	, IsAttack(false)
	, Speed(0.0f)
	, CurrentTime(0.f)
	, bDelayTime(false)
{

}

void URuleOfTheAnimInstance::NativeInitializeAnimation()
{

}

void URuleOfTheAnimInstance::NativeUpdateAnimation(float Deltaseconds)
{
	
	
	if (IsDelayUpdate(Deltaseconds))
	{
		//��ȡpawnӵ����->ת��ΪCharacter����
		if (ARuleOfTheCharacter* RuleOfTheCharacter = Cast<ARuleOfTheCharacter>(TryGetPawnOwner()))
		{
			IsAttack = RuleOfTheCharacter->IsAttack;
			Speed = RuleOfTheCharacter->GetVelocity().Size();
			IsDeath = RuleOfTheCharacter->IsDeath();
			CharacterRotator = RuleOfTheCharacter->GetActorRotation();
		}
	}
}



bool URuleOfTheAnimInstance::IsDelayUpdate(float Deltaseconds)
{
	if (!bDelayTime)
	{
		CurrentTime += Deltaseconds;
		if (CurrentTime > 0.3f)
		{
			bDelayTime = true;
		}

		return false;
	}

	return true;
}

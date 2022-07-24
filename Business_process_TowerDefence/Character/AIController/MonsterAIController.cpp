// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AIController/MonsterAIController.h"

#include "Character/CharacterCore/Towers.h"

#include "Character/Core/RuleOfTheCharacter.h"
#include "EngineUtils.h"//引用迭代器

#include "Business_process_2/FunctionUtils.h"

AActor* AMonsterAIController::FindTarget()
{
	
	if (!Target.IsValid() || !Target->IsActive())
	{
		TArray<ARuleOfTheCharacter*>TargetMainTowrsArray;
		TArray<ARuleOfTheCharacter*>TargetTowrsArray;
		for (TActorIterator<ATowers>it(GetWorld(), ATowers::StaticClass()); it; ++it)
		{
			ATowers* TheCharacter = *it;
			if (TheCharacter && TheCharacter->IsActive())
			{
				//添加到集合
				if (TheCharacter->GetCharacterType() == ECharacterType::TOWER)
				{
					TargetTowrsArray.Add(TheCharacter);
				}
				else if (TheCharacter->GetCharacterType() == ECharacterType::MAIN_TOWER)
				{
					TargetMainTowrsArray.Add(TheCharacter);
				}
			}
		}

		/*ATowers* MainTowers = Cast<ATowers>(AMonsterAIController::FindTargetRecently(TargetMainTowrsArray, GetPawn()->GetActorLocation()));
		ATowers* NorTowers = Cast<ATowers>(AMonsterAIController::FindTargetRecently(TargetTowrsArray, GetPawn()->GetActorLocation()));*/
		ATowers* MainTowers = Cast<ATowers>(FunctionUtils::FindTargetRecently(TargetMainTowrsArray, GetPawn()->GetActorLocation()));
		ATowers* NorTowers = Cast<ATowers>(FunctionUtils::FindTargetRecently(TargetTowrsArray, GetPawn()->GetActorLocation()));

		


		if (MainTowers)
		{
			return MainTowers;
		}

		return NorTowers;
	}

	return Target.Get();


}

void AMonsterAIController::AttackTarget(ARuleOfTheCharacter* InTarget)
{



}





//ARuleOfTheCharacter* AMonsterAIController::FindTargetRecently(const TArray<ARuleOfTheCharacter*>& InCharacters, const FVector& Loc)
//{
//	if (InCharacters.Num())
//	{
//		float TargetDistance = 99999999;
//		int32 Index = INDEX_NONE;
//
//		for (int32 i = 0; i < InCharacters.Num(); i++)
//		{
//			if (ARuleOfTheCharacter* TowerCharacter = InCharacters[i])
//			{
//				FVector Location = TowerCharacter->GetActorLocation();
//				FVector TmpVector = Location - Loc;
//				float Distance = TmpVector.Size();
//
//				if (Distance < TargetDistance && TowerCharacter->IsActive())
//				{
//					Index = i;
//					TargetDistance = Distance;
//				}
//			}
//		}
//
//		if (Index != INDEX_NONE)
//		{
//			return InCharacters[Index];
//		}
//	}
//
//	return NULL;
//}
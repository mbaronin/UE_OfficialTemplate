// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AIController/BTTask_Attack.h"
#include "Character/AIController/MonsterAIController.h"
#include "Character/Core/RuleOfTheCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"


EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	//获取AI 黑板
	if (AMonsterAIController* MyAIConroller = Cast<AMonsterAIController>(OwnerComp.GetOwner()))
	{
		if (UBlackboardComponent* MyBlackBoard = OwnerComp.GetBlackboardComponent())
		{
			
			if (Blackboard_Actor.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
			{
				if (ARuleOfTheCharacter* MyPawn = Cast<ARuleOfTheCharacter>(MyAIConroller->GetPawn()))
				{
					if (ARuleOfTheCharacter* TargetTower = Cast<ARuleOfTheCharacter>(MyBlackBoard->GetValueAsObject(Blackboard_Actor.SelectedKeyName)))
					{
						//MyPawn->AttackBegin();
						MyPawn->IsAttack = true;
						MyAIConroller->AttackTarget(TargetTower);
						return EBTNodeResult::Succeeded;
					}
					else
					{
						//MyPawn->AttackEnd();
						MyPawn->IsAttack = false;
						return EBTNodeResult::Succeeded;
					}
				}
			}
		}
	}

	return EBTNodeResult::Failed;
}

//初始化资源
void UBTTask_Attack::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		Blackboard_Actor.ResolveSelectedKey(*BBAsset);
	}
	else
	{
		UE_LOG(LogBehaviorTree, Warning, TEXT("Can'Initialize task:%s"), *GetName());
	}

	
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AIController/BTService_FindTarget.h"
#include "Character/AIController/MonsterAIController.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBTService_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


	//获取 AI Controller
	if (AMonsterAIController* MonsterAIController = Cast<AMonsterAIController>(OwnerComp.GetOwner()))
	{
		//获取 黑板组件
		if (UBlackboardComponent* MyBlackBoard = OwnerComp.GetBlackboardComponent())
		{
			/*
			黑板值 : 返回命名, 位置
			*/
			
			
			//寻找对象 类型转换为基类
			if (ARuleOfTheCharacter* NewTarget = Cast<ARuleOfTheCharacter>(MonsterAIController->FindTarget()))
			{
				//检测对象 与 Target指针 不符
				if (MonsterAIController->Target != NewTarget)
				{
					//停止移动 && 赋值新Target
					if (ARuleOfTheCharacter* MonsterSelf = Cast<ARuleOfTheCharacter>(MonsterAIController->GetPawn()))
					{
						MonsterSelf->GetCharacterMovement()->StopMovementImmediately();
					}
					MonsterAIController->Target = NewTarget;
				}

				//检测对象 是否存在,死亡
				if (MonsterAIController->Target.IsValid())
				{
					if (MonsterAIController->Target->IsActive())
					{
						//根据攻击距离生成导航位置
						FVector NewTargetV = MonsterAIController->GetPawn()->GetActorLocation() - MonsterAIController->Target.Get()->GetActorLocation();
						NewTargetV.Normalize();
						FVector CurrentLocation;
						if (ARuleOfTheCharacter* MonsterSelf = Cast<ARuleOfTheCharacter>(MonsterAIController->GetPawn()))
						{
							CurrentLocation = NewTargetV * MonsterSelf->AttackDistance + MonsterAIController->Target.Get()->GetActorLocation();
						}
						else
						{
							CurrentLocation = NewTargetV * 100.f + MonsterAIController->Target.Get()->GetActorLocation();
						}
						
						//返回命名 位置
						MyBlackBoard->SetValueAsObject(BlackBoardKey_Target.SelectedKeyName, MonsterAIController->Target.Get());
						MyBlackBoard->SetValueAsVector(BlackBoardKey_TargetLocation.SelectedKeyName, CurrentLocation);

					}
					//死亡 返回空
					else
					{
						MyBlackBoard->SetValueAsObject(BlackBoardKey_Target.SelectedKeyName, NULL);
						MyBlackBoard->SetValueAsVector(BlackBoardKey_TargetLocation.SelectedKeyName, FVector::ZeroVector);
					}
				}
				//不存在 返回空
				else
				{
					MyBlackBoard->SetValueAsObject(BlackBoardKey_Target.SelectedKeyName, NULL);
					MyBlackBoard->SetValueAsVector(BlackBoardKey_TargetLocation.SelectedKeyName, FVector::ZeroVector);
				}
			}
			//寻找对象转换为基类失败 返回空
			else
			{
				MyBlackBoard->SetValueAsObject(BlackBoardKey_Target.SelectedKeyName, NULL);
				MyBlackBoard->SetValueAsVector(BlackBoardKey_TargetLocation.SelectedKeyName, FVector::ZeroVector);
			}



			/*
			黑板值 : 返回距离
			*/

			//if检测对象 存在
			if (MonsterAIController->Target.IsValid())
			{
				FVector Mylocation = MonsterAIController->GetPawn()->GetActorLocation();
				FVector TMDistance = Mylocation - MonsterAIController->Target->GetActorLocation();
				//间隔距离大于攻击距离
				if (TMDistance.Size() > 2200)
				{
					//停止攻击
					if (ARuleOfTheCharacter* MonsterAI = Cast<ARuleOfTheCharacter>(MonsterAIController->GetPawn()))
					{
						//MonsterAI->AttackEnd();
						MonsterAI->IsAttack = false;
					}
				}
				//返回距离
				MyBlackBoard->SetValueAsFloat(BlackBoardKey_Distance.SelectedKeyName, TMDistance.Size());
			}
			else
			{
				MyBlackBoard->SetValueAsFloat(BlackBoardKey_Distance.SelectedKeyName, 0.f);
			}
		}
	}
}

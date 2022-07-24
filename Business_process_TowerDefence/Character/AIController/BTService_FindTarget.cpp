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


	//��ȡ AI Controller
	if (AMonsterAIController* MonsterAIController = Cast<AMonsterAIController>(OwnerComp.GetOwner()))
	{
		//��ȡ �ڰ����
		if (UBlackboardComponent* MyBlackBoard = OwnerComp.GetBlackboardComponent())
		{
			/*
			�ڰ�ֵ : ��������, λ��
			*/
			
			
			//Ѱ�Ҷ��� ����ת��Ϊ����
			if (ARuleOfTheCharacter* NewTarget = Cast<ARuleOfTheCharacter>(MonsterAIController->FindTarget()))
			{
				//������ �� Targetָ�� ����
				if (MonsterAIController->Target != NewTarget)
				{
					//ֹͣ�ƶ� && ��ֵ��Target
					if (ARuleOfTheCharacter* MonsterSelf = Cast<ARuleOfTheCharacter>(MonsterAIController->GetPawn()))
					{
						MonsterSelf->GetCharacterMovement()->StopMovementImmediately();
					}
					MonsterAIController->Target = NewTarget;
				}

				//������ �Ƿ����,����
				if (MonsterAIController->Target.IsValid())
				{
					if (MonsterAIController->Target->IsActive())
					{
						//���ݹ����������ɵ���λ��
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
						
						//�������� λ��
						MyBlackBoard->SetValueAsObject(BlackBoardKey_Target.SelectedKeyName, MonsterAIController->Target.Get());
						MyBlackBoard->SetValueAsVector(BlackBoardKey_TargetLocation.SelectedKeyName, CurrentLocation);

					}
					//���� ���ؿ�
					else
					{
						MyBlackBoard->SetValueAsObject(BlackBoardKey_Target.SelectedKeyName, NULL);
						MyBlackBoard->SetValueAsVector(BlackBoardKey_TargetLocation.SelectedKeyName, FVector::ZeroVector);
					}
				}
				//������ ���ؿ�
				else
				{
					MyBlackBoard->SetValueAsObject(BlackBoardKey_Target.SelectedKeyName, NULL);
					MyBlackBoard->SetValueAsVector(BlackBoardKey_TargetLocation.SelectedKeyName, FVector::ZeroVector);
				}
			}
			//Ѱ�Ҷ���ת��Ϊ����ʧ�� ���ؿ�
			else
			{
				MyBlackBoard->SetValueAsObject(BlackBoardKey_Target.SelectedKeyName, NULL);
				MyBlackBoard->SetValueAsVector(BlackBoardKey_TargetLocation.SelectedKeyName, FVector::ZeroVector);
			}



			/*
			�ڰ�ֵ : ���ؾ���
			*/

			//if������ ����
			if (MonsterAIController->Target.IsValid())
			{
				FVector Mylocation = MonsterAIController->GetPawn()->GetActorLocation();
				FVector TMDistance = Mylocation - MonsterAIController->Target->GetActorLocation();
				//���������ڹ�������
				if (TMDistance.Size() > 2200)
				{
					//ֹͣ����
					if (ARuleOfTheCharacter* MonsterAI = Cast<ARuleOfTheCharacter>(MonsterAIController->GetPawn()))
					{
						//MonsterAI->AttackEnd();
						MonsterAI->IsAttack = false;
					}
				}
				//���ؾ���
				MyBlackBoard->SetValueAsFloat(BlackBoardKey_Distance.SelectedKeyName, TMDistance.Size());
			}
			else
			{
				MyBlackBoard->SetValueAsFloat(BlackBoardKey_Distance.SelectedKeyName, 0.f);
			}
		}
	}
}

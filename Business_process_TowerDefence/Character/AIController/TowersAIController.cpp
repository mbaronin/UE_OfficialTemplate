// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AIController/TowersAIController.h"

#include "Character/CharacterCore/Monster.h"
#include "Character/CharacterCore/Towers.h"
#include "EngineUtils.h"

#include "Business_process_2/FunctionUtils.h"

ATowersAIController::ATowersAIController()
	:Heartbeat(0.0f)
{

}



void ATowersAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//0.5�봥��һ�η���
	Heartbeat += DeltaTime;
	if (Heartbeat >= 0.5f)
	{
		BTService_FindTarget();
		Heartbeat = 0.0f;
	}

	if (TArrayMonsters.Num())
	{
		if (ATowers* Towers = GetPawn<ATowers>())
		{
			//if target ������ �� ���¸�ֵ
			if (!Target.IsValid() || !Target->IsActive())
			{
				Target = Cast<ARuleOfTheCharacter>(FunctionUtils::FindTargetRecently(TArrayMonsters, GetPawn()->GetActorLocation()));
			}
			//ʹ����ָ��target
			if (Target.IsValid())
			{
				Towers->TowersRotator = FRotationMatrix::MakeFromX(Target->GetActorLocation() - GetPawn()->GetActorLocation()).Rotator();
				
				GetPawn()->SetActorRotation(Towers->TowersRotator);
			}
		}
	}

}



//��������(������Χ��) ��ȡ����target(monster����)
void ATowersAIController::BTService_FindTarget()
{
	TArrayMonsters.Empty();
	if (ATowers* Towers = GetPawn<ATowers>())
	{
		if (Towers->IsActive())
		{
			for (TActorIterator<AMonster>it(GetWorld(), AMonster::StaticClass()); it; ++it)
			{
				if (AMonster* TheCharacter = *it)
				{
					if (TheCharacter->IsActive())
					{
						FVector TDistance = TheCharacter->GetActorLocation() - GetPawn()->GetActorLocation();
						if (TDistance.Size() <= 1600)
						{
							TArrayMonsters.Add(TheCharacter);
						}
					}
				}
			}

			AttackTarget(Target.Get());
		}
	}

}

void ATowersAIController::AttackTarget(ARuleOfTheCharacter* InTarget)
{
	if (ATowers* Towers = GetPawn<ATowers>())
	{
		if (TArrayMonsters.Num() > 0)
		{
			//Towers->AttackBegin();
			Towers->IsAttack = true;
		}
		else
		{
			//Towers->AttackEnd();
			Towers->IsAttack = false;
		}
	}

}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Core/RuleOfTheCharacter.h"

#include "Components/BoxComponent.h"//���߲�׽����
#include "Components/ArrowComponent.h"//�����
#include "Components/WidgetComponent.h"//��Ϣ��ʾ��
#include "UI/GameUI/UMG/UI_Health.h"	//Ѫ��UI

#include "DrawText.h"					//�˺���ֵ

#include "Components/StaticMeshComponent.h"			//���������Ч
#include "Particles/ParticleSystemComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Particles\TypeData\ParticleModuleTypeDataMesh.h"//��ȡ��Ч���ģ��
#include "Particles/ParticleEmitter.h"
#include "Global\ManageCore.h"//��ȡ����Meshģ��
#include "Global\CachePoolManagement.h"
#include "Particles\ParticleLODLevel.h"

#include "Business_process_2\FunctionUtils.h"

//#include "Global\Core\ManageCore.h"
//#include "Global\CachePoolManagement.h"


// Sets default values
ARuleOfTheCharacter::ARuleOfTheCharacter()
	:DelayDeath(10.f)
	, IsAttack(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GUID = FGuid::NewGuid();

	

	HomePoint = CreateDefaultSubobject<USceneComponent>(TEXT("HomePoint"));
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	OpenFriePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("OpenFilePoint"));
	TraceShowCharacterInformation = CreateDefaultSubobject<UBoxComponent>(TEXT("TraceShowCharacterInformation"));

	HomePoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Widget->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	OpenFriePoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TraceShowCharacterInformation->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//����Ԥ��Scanning
	TraceShowCharacterInformation->SetCollisionProfileName("Click");
	//���BOXԤ���С
	TraceShowCharacterInformation->SetBoxExtent(FVector(38.f, 38.f, 100.f));

	

}

// Called when the game starts or when spawned
void ARuleOfTheCharacter::BeginPlay()
{
	Super::BeginPlay();

	//���ɽ�ɫ��Ҫ����һ��Ĭ�ϵĿ���
	if (!GetController())
	{
		SpawnDefaultController();
	}
	//��������� ->�� ��-> OnClicked����
	TraceShowCharacterInformation->OnClicked.AddDynamic(this, &ARuleOfTheCharacter::OnClicked);

	//delay 0.1 �� ���� ����UI
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ARuleOfTheCharacter::AdvanceTimer, 0.1f, true);
	/*///��������Ѫ��
	if (Widget){Widget->SetVisibility(false, false);}*/
	
}

void ARuleOfTheCharacter::AdvanceTimer()
{
	//������ɣ�ֹͣ���ж�ʱ����
	if (CountdownTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		//GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
	}
	//��ʱ������ʱ��ִ��Ҫִ�е����������
	// 
	//ˢ��UI
	UpdateUI();
	//��ʼ������
	if (GetCharacterData())
	{
		AttackDistance = GetCharacterData()->AttackDistance;
	}
	
}



// Called every frame
void ARuleOfTheCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	////����ui
	////
	////
	//UpdateUI();

}


//�ܵ��˺���ʽ
float GetDamage(ARuleOfTheCharacter* Enemy, ARuleOfTheCharacter* Owner)
{
	if (Enemy && Owner)
	{
		if (FCharacterData* OwnerCharacterData = Owner->GetCharacterData())
		{
			if (FCharacterData* EnemyCharacterData = Enemy->GetCharacterData())
			{
				///          �˺���ʾ
				/*GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, 
					FString::SanitizeFloat(EnemyCharacterData->GetAttack() / ((OwnerCharacterData->GetArmor() / 100.f) + 1.f)));*/
				
				return EnemyCharacterData->GetAttack() / ((OwnerCharacterData->GetArmor() / 100.f) + 1.f);
			}
		}
	}
	return 0.0f;
}


float ARuleOfTheCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	
	float DamgageValue = 0.f;

	//��ʱʹ��
	

	DamgageValue = GetDamage(Cast<ARuleOfTheCharacter>(DamageCauser), this);
	GetCharacterData()->Health -= DamgageValue;
	UpdateUI();
	//
	//Owner		��ʽ		�˺�		��ɫ
	auto DrawGameText = [&](ARuleOfTheCharacter* InOwner, const TCHAR* InText, float InDamgageValue, FLinearColor InColor)
	{
		if (DrawTextClass)
		{
			if (ADrawText* MyValueText = GetWorld()->SpawnActor<ADrawText>(DrawTextClass, InOwner->GetActorLocation(), FRotator::ZeroRotator))
			{
				//FString DamageText = FString::Printf(InText, InDamgageValue);
				FString DamageText = FString::Printf(TEXT("-%0.f"), InDamgageValue);

				MyValueText->SetTextBlock(DamageText, InColor, InDamgageValue / InOwner->GetCharacterData()->GetMaxHealth());
			}
		}
	};
	
		if (DamgageValue)
		{
			//������������
			DrawGameText(this, TEXT("-%0.f"), DamgageValue, FLinearColor::Red);
		}
		//�����ж�
		if (!IsActive())
		{
			GetCharacterData()->Health = 0.0f;
			SetLifeSpan(DelayDeath);


			Widget->SetVisibility(false);
			GetGameState()->RemoveCharacterData(GUID);

			//���Ӿ���ֵ
			//...
		}



/*

	//��ȡ ����,�˺�����,��������
	if (FCharacterData* InCharacterData = GetCharacterData())
	{
		if (1)//URuleOfTheDamage* DamageClass = DamageEvent.DamageTypeClass->GetDefaultObject<URuleOfTheDamage>())
		{
			if (1)//const FSkillData* SkillData = DamageClass->SkillData)
			{
				
				auto DrawGameText = [&](ARuleOfTheCharacter* InOwner, const TCHAR* InText, float InDamgageValue, FLinearColor InColor)
				{
					if (DrawTextClass)
					{
						if (ADrawText* MyValueText = GetWorld()->SpawnActor<ADrawText>(DrawTextClass, InOwner->GetActorLocation(), FRotator::ZeroRotator))
						{
							FString DamageText = FString::Printf(InText, InDamgageValue);
							MyValueText->SetTextBlock(DamageText, InColor, InDamgageValue / InOwner->GetCharacterData()->GetMaxHealth());
						}
					}
				};

				if (SkillData->SkillType.SkillEffectType == ESkillEffectType::SUBTRACT)
				{
					DamgageValue = Expression::GetDamage(Cast<ARuleOfTheCharacter>(DamageCauser), this);
					if (DamgageValue)
					{
						InCharacterData->Health -= DamgageValue;
						//������������
						DrawGameText(this, TEXT("-%0.f"), DamgageValue, FLinearColor::Red);
					}

					if (SkillData->AttackSpeed)
					{
						InCharacterData->AttackSpeed -= SkillData->AttackSpeed;
						//������������
						DrawGameText(this, TEXT("-%0.f"), SkillData->AttackSpeed, FLinearColor::Black);
					}
					if (SkillData->PhysicalAttack)
					{
						InCharacterData->PhysicalAttack -= SkillData->PhysicalAttack;
						//������������
						DrawGameText(this, TEXT("-%0.f"), SkillData->PhysicalAttack, FLinearColor::Black);
					}
					if (SkillData->Armor)
					{
						InCharacterData->Armor -= SkillData->Armor;
						//������������
						DrawGameText(this, TEXT("-%0.f"), SkillData->Armor, FLinearColor::Black);
					}
				}
				else if (SkillData->SkillType.SkillEffectType == ESkillEffectType::ADD)
				{
					if (SkillData->PhysicalAttack)
					{
						InCharacterData->PhysicalAttack += SkillData->PhysicalAttack;
						//������������
						DrawGameText(this, TEXT("+%0.f"), SkillData->PhysicalAttack, FLinearColor::Blue);
					}

					if (SkillData->Armor)
					{
						InCharacterData->Armor += SkillData->Armor;
						//������������
						DrawGameText(this, TEXT("+%0.f"), SkillData->Armor, FLinearColor::White);
					}

					if (SkillData->AttackSpeed)
					{
						InCharacterData->AttackSpeed += SkillData->AttackSpeed;
						//������������
						DrawGameText(this, TEXT("+%0.f"), SkillData->AttackSpeed, FLinearColor::White);
					}

					if (SkillData->Health)
					{
						InCharacterData->Health += SkillData->Health;
						if (InCharacterData->Health > InCharacterData->MaxHealth)
						{
							InCharacterData->Health = InCharacterData->MaxHealth;
						}

						//������������
						DrawGameText(this, TEXT("+%0.f"), SkillData->Health, FLinearColor::Green);
					}
				}

				//�����ж�
				if (!IsActive())
				{
					//���� ֪ͨ��ͼ
					CharacterDeath();

					//���ͻ���
					if (GetPlayerState()->GetPlayerData().Team != GetTeamType())
					{
						GetPlayerState()->GetPlayerData().GameGold += InCharacterData->Glod;
					}

					GetCharacterData()->Health = 0.0f;
					SetLifeSpan(DelayDeath);
					
					Widget->SetVisibility(false);

					//˭ɱ���� ˭�͵õ����ṩ����ྭ��
					if (ARuleOfTheCharacter* CauserCharacter = Cast<ARuleOfTheCharacter>(DamageCauser))
					{
						if (CauserCharacter->IsActive())
						{
							if (CauserCharacter->GetCharacterData()->UpdateEP(InCharacterData->AddEmpiricalValue))
							{

							}

							DrawGameText(CauserCharacter, TEXT("+EP %0.f"), InCharacterData->AddEmpiricalValue, FLinearColor::Yellow);
						}

						//Ѱ�ҷ�Χ������ĵ��� ����
						TArray<ARuleOfTheCharacter*> EnemyCharacters;
						StoneDefenceUtils::FindRangeTargetRecently(this, 1000.f, EnemyCharacters);
						for (ARuleOfTheCharacter* InEnemy : EnemyCharacters)
						{
							if (InEnemy != CauserCharacter)
							{
								if (InEnemy->IsActive())
								{
									if (InEnemy->GetCharacterData()->UpdateEP(InCharacterData->AddEmpiricalValue * 0.3f))
									{

									}

									DrawGameText(InEnemy, TEXT("+EP %0.f"), InCharacterData->AddEmpiricalValue, FLinearColor::Yellow);
								}
							}
						}
					}

					GetGameState()->RemoveCharacterData(GUID);
				}
				else
				{
					SubmissionSkillRequest(SkillData->ID);
				}
			}
		}
	}
	*/

	return DamgageValue;
}

void ARuleOfTheCharacter::UpdateUI()
{
	

	if (Widget)
	{
		Widget->SetVisibility(true, false);
		if (const FCharacterData* InCharacterData = GetCharacterData())
		{
			if (InCharacterData->IsValid())
			{
				if (UUI_Health* HealthUI = Cast<UUI_Health>(Widget->GetUserWidgetObject()))
				{
					HealthUI->SetTitle(InCharacterData->Name.ToString());
					HealthUI->SetHealth(GetHealth() / GetMaxHealth());
				}
			}
		}
	}
}

ECharacterType ARuleOfTheCharacter::GetCharacterType()
{
	return ECharacterType::NONE;
}

bool ARuleOfTheCharacter::IsDeath()
{
	return GetHealth() <= 0.f;
}

float ARuleOfTheCharacter::GetHealth()
{
	if (FCharacterData* InCharacterData = GetCharacterData())
	{
		//��ӡ��ǰѪ��
		/*check(GEngine != nullptr);
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::SanitizeFloat(InCharacterData->Health));*/

		return InCharacterData->Health;
	}
	return 0.f;
}

float ARuleOfTheCharacter::GetMaxHealth()
{
	if (FCharacterData* InCharacterData = GetCharacterData())
	{
		return InCharacterData->GetMaxHealth();
	}

	return 100.f;
}

FCharacterData* ARuleOfTheCharacter::GetCharacterData()
{
	if (GetGameState())
	{
		return GetGameState()->GetCharacterData(GUID);
	}

	return nullptr;
}




UStaticMesh* ARuleOfTheCharacter::GetMesh(FTransform& Transform, int32 MeshID)
{
	TArray<USceneComponent*> SceneComponent;
	RootComponent->GetChildrenComponents(true, SceneComponent);
	//������������
	for (auto& Tmp : SceneComponent)
	{
		//����̬������,��Ч,���������� ת��Ϊstatic mesh
		//��̬������
		if (UStaticMeshComponent* NewMeshComponent = Cast<UStaticMeshComponent>(Tmp))
		{
			if (NewMeshComponent->GetStaticMesh())
			{
				Transform = NewMeshComponent->GetComponentTransform();
				return NewMeshComponent->GetStaticMesh();
			}
		}
		//��Ч 
		else if (UParticleSystemComponent* NewParticleSystemComponent = Cast<UParticleSystemComponent>(Tmp))
		{
			UStaticMesh* NewStaticMesh = nullptr;
			if (NewParticleSystemComponent->Template && NewParticleSystemComponent->Template->Emitters.Num() > 0)
			{//���ڷ�����(isvalid)
				for (const UParticleEmitter* Tmp1 : NewParticleSystemComponent->Template->Emitters)
				{//����������
					if (Tmp1->LODLevels[0]->bEnabled)
					{//��ȡLOD0;
						if (UParticleModuleTypeDataMesh* MyParticleDataMesh = Cast<UParticleModuleTypeDataMesh>(Tmp1->LODLevels[0]->TypeDataModule))
						{
							if (MyParticleDataMesh->Mesh)
							{
								NewStaticMesh = MyParticleDataMesh->Mesh;
								break;
							}
						}
					}
				}
			}
			if (NewStaticMesh)
			{
				Transform = NewParticleSystemComponent->GetComponentTransform();
				return NewStaticMesh;
			}
		}
		//����������
		else if (USkeletalMeshComponent* NewSkeletalMeshComponent = Cast<USkeletalMeshComponent>(Tmp))
		{
			Transform = NewSkeletalMeshComponent->GetComponentTransform();
			NewSkeletalMeshComponent->SetRelativeTransform(FTransform::Identity);
			NewSkeletalMeshComponent->SetWorldTransform(FTransform::Identity);
			NewSkeletalMeshComponent->SetRelativeRotation(Transform.GetRotation());

			
			FManagementCore<FDollMeshPoolManage> GDollMeshPoolManage;

			if (UStaticMesh* NewMesh1 = GDollMeshPoolManage.Get(GetWorld())->GetStaticMesh(MeshID))
			{
				return NewMesh1;
			}
			else
			{
				if (UStaticMesh* NewMesh = FunctionUtils::SkeletalMeshToStaticMesh(NewSkeletalMeshComponent))
				{
					GDollMeshPoolManage.Get(GetWorld())->Add(MeshID, NewMesh);
					return NewMesh;
				}
			}
		}
	}
	return nullptr;
}

bool ARuleOfTheCharacter::IsActive()
{
	 return !IsDeath(); 

}

void ARuleOfTheCharacter::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
}

//bool ARuleOfTheCharacter::IsTeam()
//{
//	return false;
//}

//void ARuleOfTheCharacter::AttackBegin()
//{
//}
//
//void ARuleOfTheCharacter::AttackEnd()
//{
//}
//
//void ARuleOfTheCharacter::CharacterDeath()
//{
//}
//
//void ARuleOfTheCharacter::AnimTag()
//{
//}

//bool ARuleOfTheCharacter::IsTeam()
//{
//	return false;
//}

//// Called to bind functionality to input
//void ARuleOfTheCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}


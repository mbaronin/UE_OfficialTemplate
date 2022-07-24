// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Core/RuleOfTheCharacter.h"

#include "Components/BoxComponent.h"//射线捕捉对象
#include "Components/ArrowComponent.h"//开火点
#include "Components/WidgetComponent.h"//信息提示框
#include "UI/GameUI/UMG/UI_Health.h"	//血条UI

#include "DrawText.h"					//伤害数值

#include "Components/StaticMeshComponent.h"			//网格体和特效
#include "Particles/ParticleSystemComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Particles\TypeData\ParticleModuleTypeDataMesh.h"//提取特效组件模型
#include "Particles/ParticleEmitter.h"
#include "Global\ManageCore.h"//提取骨骼Mesh模型
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

	//设置预设Scanning
	TraceShowCharacterInformation->SetCollisionProfileName("Click");
	//检测BOX预设大小
	TraceShowCharacterInformation->SetBoxExtent(FVector(38.f, 38.f, 100.f));

	

}

// Called when the game starts or when spawned
void ARuleOfTheCharacter::BeginPlay()
{
	Super::BeginPlay();

	//生成角色需要生成一个默认的控制
	if (!GetController())
	{
		SpawnDefaultController();
	}
	//光标点击检测框 ->绑定 到-> OnClicked函数
	TraceShowCharacterInformation->OnClicked.AddDynamic(this, &ARuleOfTheCharacter::OnClicked);

	//delay 0.1 秒 触发 更新UI
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ARuleOfTheCharacter::AdvanceTimer, 0.1f, true);
	/*///开局隐藏血条
	if (Widget){Widget->SetVisibility(false, false);}*/
	
}

void ARuleOfTheCharacter::AdvanceTimer()
{
	//倒数完成，停止运行定时器。
	if (CountdownTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		//GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
	}
	//定时器结束时，执行要执行的特殊操作。
	// 
	//刷新UI
	UpdateUI();
	//初始化属性
	if (GetCharacterData())
	{
		AttackDistance = GetCharacterData()->AttackDistance;
	}
	
}



// Called every frame
void ARuleOfTheCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	////测试ui
	////
	////
	//UpdateUI();

}


//受到伤害公式
float GetDamage(ARuleOfTheCharacter* Enemy, ARuleOfTheCharacter* Owner)
{
	if (Enemy && Owner)
	{
		if (FCharacterData* OwnerCharacterData = Owner->GetCharacterData())
		{
			if (FCharacterData* EnemyCharacterData = Enemy->GetCharacterData())
			{
				///          伤害显示
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

	//临时使用
	

	DamgageValue = GetDamage(Cast<ARuleOfTheCharacter>(DamageCauser), this);
	GetCharacterData()->Health -= DamgageValue;
	UpdateUI();
	//
	//Owner		格式		伤害		颜色
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
			//绘制受伤字体
			DrawGameText(this, TEXT("-%0.f"), DamgageValue, FLinearColor::Red);
		}
		//死亡判定
		if (!IsActive())
		{
			GetCharacterData()->Health = 0.0f;
			SetLifeSpan(DelayDeath);


			Widget->SetVisibility(false);
			GetGameState()->RemoveCharacterData(GUID);

			//增加经验值
			//...
		}



/*

	//获取 数据,伤害类型,技能数据
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
						//绘制受伤字体
						DrawGameText(this, TEXT("-%0.f"), DamgageValue, FLinearColor::Red);
					}

					if (SkillData->AttackSpeed)
					{
						InCharacterData->AttackSpeed -= SkillData->AttackSpeed;
						//绘制受伤字体
						DrawGameText(this, TEXT("-%0.f"), SkillData->AttackSpeed, FLinearColor::Black);
					}
					if (SkillData->PhysicalAttack)
					{
						InCharacterData->PhysicalAttack -= SkillData->PhysicalAttack;
						//绘制受伤字体
						DrawGameText(this, TEXT("-%0.f"), SkillData->PhysicalAttack, FLinearColor::Black);
					}
					if (SkillData->Armor)
					{
						InCharacterData->Armor -= SkillData->Armor;
						//绘制受伤字体
						DrawGameText(this, TEXT("-%0.f"), SkillData->Armor, FLinearColor::Black);
					}
				}
				else if (SkillData->SkillType.SkillEffectType == ESkillEffectType::ADD)
				{
					if (SkillData->PhysicalAttack)
					{
						InCharacterData->PhysicalAttack += SkillData->PhysicalAttack;
						//绘制受伤字体
						DrawGameText(this, TEXT("+%0.f"), SkillData->PhysicalAttack, FLinearColor::Blue);
					}

					if (SkillData->Armor)
					{
						InCharacterData->Armor += SkillData->Armor;
						//绘制受伤字体
						DrawGameText(this, TEXT("+%0.f"), SkillData->Armor, FLinearColor::White);
					}

					if (SkillData->AttackSpeed)
					{
						InCharacterData->AttackSpeed += SkillData->AttackSpeed;
						//绘制受伤字体
						DrawGameText(this, TEXT("+%0.f"), SkillData->AttackSpeed, FLinearColor::White);
					}

					if (SkillData->Health)
					{
						InCharacterData->Health += SkillData->Health;
						if (InCharacterData->Health > InCharacterData->MaxHealth)
						{
							InCharacterData->Health = InCharacterData->MaxHealth;
						}

						//绘制受伤字体
						DrawGameText(this, TEXT("+%0.f"), SkillData->Health, FLinearColor::Green);
					}
				}

				//死亡判定
				if (!IsActive())
				{
					//死亡 通知蓝图
					CharacterDeath();

					//奖赏机制
					if (GetPlayerState()->GetPlayerData().Team != GetTeamType())
					{
						GetPlayerState()->GetPlayerData().GameGold += InCharacterData->Glod;
					}

					GetCharacterData()->Health = 0.0f;
					SetLifeSpan(DelayDeath);
					
					Widget->SetVisibility(false);

					//谁杀死我 谁就得到我提供的最多经验
					if (ARuleOfTheCharacter* CauserCharacter = Cast<ARuleOfTheCharacter>(DamageCauser))
					{
						if (CauserCharacter->IsActive())
						{
							if (CauserCharacter->GetCharacterData()->UpdateEP(InCharacterData->AddEmpiricalValue))
							{

							}

							DrawGameText(CauserCharacter, TEXT("+EP %0.f"), InCharacterData->AddEmpiricalValue, FLinearColor::Yellow);
						}

						//寻找范围内最近的敌人 升级
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
		//打印当前血量
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
	//遍历所有子项
	for (auto& Tmp : SceneComponent)
	{
		//将静态网格体,特效,骨骼网格体 转换为static mesh
		//静态网格体
		if (UStaticMeshComponent* NewMeshComponent = Cast<UStaticMeshComponent>(Tmp))
		{
			if (NewMeshComponent->GetStaticMesh())
			{
				Transform = NewMeshComponent->GetComponentTransform();
				return NewMeshComponent->GetStaticMesh();
			}
		}
		//特效 
		else if (UParticleSystemComponent* NewParticleSystemComponent = Cast<UParticleSystemComponent>(Tmp))
		{
			UStaticMesh* NewStaticMesh = nullptr;
			if (NewParticleSystemComponent->Template && NewParticleSystemComponent->Template->Emitters.Num() > 0)
			{//存在发射器(isvalid)
				for (const UParticleEmitter* Tmp1 : NewParticleSystemComponent->Template->Emitters)
				{//遍历发射器
					if (Tmp1->LODLevels[0]->bEnabled)
					{//提取LOD0;
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
		//骨骼网格体
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


// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Bullet/RuleOfTheBullet.h"
#include "Particles/ParticleSystemComponent.h"//粒子特效
#include "Components/SphereComponent.h"//球形组件
#include "GameFramework/ProjectileMovementComponent.h"//抛射物组件


#include "Character/Core/RuleOfTheCharacter.h"
#include "Kismet/GameplayStatics.h"				//特效
//#include "GameFramework/DamageType.h"
#include "Character/AIController/RuleOfTheAIController.h"
#include "EngineUtils.h"						//使用迭代器 遍历
#include "Components/ArrowComponent.h"			//获取开火点
#include "Components/SplineComponent.h"			//追踪路径
//#include "Core/GameCore/TowersDefenceGameState.h"
#include "Data/Core/SkillData.h"

#include "Character/Bullet/RuleOfTheDamage.h"

// Sets default values
ARuleOfTheBullet::ARuleOfTheBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkillID = INDEX_NONE;
	ChainAttackCount = 3;
	SplineOffsetHorizontal = 0.0f;
	SplineOffsetVertical = 0.0f;
	CurrentSplineTime = 0.0f;
	Spline = nullptr;
	AutoSplineOffset = false;

	BoxDamage = CreateDefaultSubobject<USphereComponent>(TEXT("BulletNoxDamage"));
	RootBullet = CreateDefaultSubobject<USceneComponent>(TEXT("BulletRootBullet"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletProjectileMovement"));

	RootComponent = RootBullet;
	BoxDamage->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->InitialSpeed = 1600.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;		//重力0
	ProjectileMovement->UpdatedComponent = BoxDamage;		
	BulletType = EBulletType::BULLET_NONE;					//默认子弹种类

	//SubmissionSkillRequestType = ESubmissionSkillRequestType::AUTO;
	
	InitialLifeSpan = 4.0f;									//4秒后自动销毁
}

// Called when the game starts or when spawned
void ARuleOfTheBullet::BeginPlay()
{
	Super::BeginPlay();
	//绑定 BoxDamage开始重叠 到函数
	BoxDamage->OnComponentBeginOverlap.AddUniqueDynamic(this, &ARuleOfTheBullet::BeginOverlap);

	InitSkill();

}

// Called every frame
void ARuleOfTheBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	//两种逐帧显示的攻击方式
	if ((BulletType == EBulletType::BULLET_CHAIN) || (BulletType == EBulletType::BULLET_TRACK_LINE_SP))
	{
		if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(GetInstigator()))
		{
			if (ARuleOfTheAIController* InstigatorController = Cast<ARuleOfTheAIController>(InstigatorCharacter->GetController()))
			{
				if (ARuleOfTheCharacter* TargetCharacter = InstigatorController->Target.Get())
				{
					switch (BulletType)
					{
					case EBulletType::BULLET_CHAIN:
					{
						//SceneComponent容器
						TArray<USceneComponent*> SceneComponent;
						//获取所有子类Component (是否包含所有依赖, 容器)
						RootComponent->GetChildrenComponents(true, SceneComponent);
						//遍历
						for (auto& Tmp : SceneComponent)
						{
							if (UParticleSystemComponent* ParticleSystem = Cast<UParticleSystemComponent>(Tmp))
							{
								//设置原点 目标点
								ParticleSystem->SetBeamSourcePoint(0, InstigatorCharacter->GetFirePoint()->GetComponentLocation(), 0);
								ParticleSystem->SetBeamTargetPoint(0, TargetCharacter->GetHommingPoint()->GetComponentLocation(), 0);
							}
						}
						break;
					}
					case EBulletType::BULLET_TRACK_LINE_SP:
					{
						if (Spline)
						{
							//..刷新追踪点
							Spline->RemoveSplinePoint(2);
							Spline->AddSplinePoint(TargetCharacter->GetActorLocation(), ESplineCoordinateSpace::Local);
							

							FVector DistanceVector = TargetCharacter->GetActorLocation() - InstigatorCharacter->GetActorLocation();
							CurrentSplineTime += DeltaTime;
							/// <summary>
							///							 生成时间							生成时间
							/// 走过的距离 = 路径长度 * ______________	 = 路径长度 * _____________________
							///							命中所需时间						(直线距离/初始速度)
							/// </summary>
							float DistanceTraveled = Spline->GetSplineLength() * (CurrentSplineTime / (DistanceVector.Size() / ProjectileMovement->InitialSpeed));
							//通过走过的距离 获得位置和旋转
							FVector Loction = Spline->GetWorldLocationAtDistanceAlongSpline(DistanceTraveled);
							FRotator Rotator = Spline->GetRotationAtDistanceAlongSpline(DistanceTraveled, ESplineCoordinateSpace::Local);

							SetActorLocationAndRotation(Loction, Rotator);

							//接近target
							if ((Loction - TargetCharacter->GetActorLocation()).Size() <= 10.f)
							{
								FHitResult SweepResult;
								SweepResult.Location = Loction;
								BeginOverlap(nullptr, TargetCharacter, nullptr, 0, false, SweepResult);
							}
						}
						break;
					}
					}
					if (!TargetCharacter->IsActive())
					{
						Destroy();
					}
				}
				else
				{
					Destroy();
				}
			}
		}

	}
}

const FSkillData* ARuleOfTheBullet::GetSkillData()
{
	if (ATowerDefenceGameState* InGameState = GetWorld()->GetGameState<ATowerDefenceGameState>())
	{
		return InGameState->GetSkillData(SkillID);
	}
	
	return nullptr;
}





/// <summary>
/// 初始生成子弹类型
/// </summary>
void ARuleOfTheBullet::InitSkill()
{
	//获取 发射者
	if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(GetInstigator()))
	{
		//获取 发射者Controller
		if (ARuleOfTheAIController* InstigatorController = Cast<ARuleOfTheAIController>(InstigatorCharacter->GetController()))
		{
			//获取 目标
			if (ARuleOfTheCharacter* TargetCharacter = InstigatorController->Target.Get())
			{
				//枪口特效
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OpenFireParticle, GetActorLocation());

				switch (BulletType)
				{
				case EBulletType::BULLET_NONE:																//不产生任何效果
					break;
				case EBulletType::BULLET_DIRECT_LINE:														//直线攻击，穿透
					break;
				case EBulletType::BULLET_LINE:																//直线攻击，不穿透；
					break;
				case EBulletType::BULLET_TRACK_LINE:														//跟踪类型
					ProjectileMovement->bIsHomingProjectile = true;//是否跟踪
					ProjectileMovement->bRotationFollowsVelocity = true;//旋转跟随运动
					ProjectileMovement->HomingAccelerationMagnitude = 8000.f;//加速度
					ProjectileMovement->HomingTargetComponent = TargetCharacter->GetHommingPoint(); //跟踪组件
					break;
				case EBulletType::BULLET_TRACK_LINE_SP:														//跟踪类型SPline
				{
					ProjectileMovement->StopMovementImmediately();

					//创建 && 注册组件
					Spline = NewObject<USplineComponent>(this, TEXT("SplineInstance"));
					Spline->RegisterComponent();

					//Instigator和target 中心点坐标 && 距离 && 偏移 && 高度
					FVector Position = (InstigatorCharacter->GetActorLocation() + TargetCharacter->GetActorLocation()) / 2;
					FVector DistanceVector = InstigatorCharacter->GetActorLocation() - TargetCharacter->GetActorLocation();
					
					
					if (AutoSplineOffset)
					{
						srand((unsigned)time(NULL));
						Position.Y += rand() % 200;
						Position.Z = DistanceVector.Size()  * 0.25f;
					}
					else
					{
						Position.Y += SplineOffsetHorizontal;
						Position.Z += SplineOffsetVertical;
					}
					
					//index 0, 开始位置, 
					Spline->SetLocationAtSplinePoint(0, GetActorLocation(), ESplineCoordinateSpace::Local);
					//index 1, 路径位置
					Spline->SetLocationAtSplinePoint(1, Position, ESplineCoordinateSpace::Local);
					//添加Target位置(在Tick中更新位置)
					Spline->AddSplinePoint(TargetCharacter->GetActorLocation(), ESplineCoordinateSpace::Local);
					break;
				}
				case EBulletType::BULLET_RANGE_THROW:														//范围伤害，丢手雷；
				{
					ProjectileMovement->StopMovementImmediately();
					
					ProjectileMovement->ProjectileGravityScale = 3.f;

					///// <summary>
					/////					 (180 / PI) * Asin[ (Distance*-g) / (v*v) ] 
					///// 发射角度()  = 90 - ____________________________________________
					/////										2
					///// </summary>
					float Distance = (TargetCharacter->GetActorLocation() - GetActorLocation()).Size();
					float v = ProjectileMovement->InitialSpeed;
					FRotator LaunchAngle = GetActorRotation();

					LaunchAngle.Pitch = 90 -((180 / PI) * FMath::Asin((Distance * -ProjectileMovement->GetGravityZ()) / (v * v))) / 2;
				
					SetActorRotation(LaunchAngle);
					ProjectileMovement->SetVelocityInLocalSpace(FVector(1.0f, 0.f, 0.f) * ProjectileMovement->InitialSpeed);
					break;
				}
					
				case EBulletType::BULLET_RANGE:																//范围伤害，子弹溅射；
					ProjectileMovement->StopMovementImmediately();//停止移动
					BoxDamage->SetCollisionEnabled(ECollisionEnabled::NoCollision);//清除碰撞
					RadialDamage(GetActorLocation(), Cast<ARuleOfTheCharacter>(GetInstigator()));//应用圆形范围伤害

					break;
				case EBulletType::BULLET_CHAIN:																//链条类型，持续伤害类型;
				{
					ProjectileMovement->StopMovementImmediately();
					BoxDamage->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					//生成特效绑定到target
					UGameplayStatics::SpawnEmitterAttached(OpenFireParticle, InstigatorCharacter->GetHommingPoint());
					UGameplayStatics::SpawnEmitterAttached(DamageParticle, TargetCharacter->GetHommingPoint());
					//应用持续伤害
					GetWorld()->GetTimerManager().SetTimer(ChainAttackHandle, this, &ARuleOfTheBullet::ChainAttack, 0.1f);
					//SubmissionSkillRequest();
					break;
				}
				default:
					break;
				}
			}
		}
	}
}





/// 命中反馈
void ARuleOfTheBullet::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (const FSkillData* InData = GetSkillData()){}
	
	//获得 发射者
	if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(GetInstigator()))
	{
		//获得 命中目标
		if (ARuleOfTheCharacter* OtherCharacter = Cast<ARuleOfTheCharacter>(OtherActor))
		{
			////临时函数  判断 不同队伍
			//auto VerifyConsistency = [&]()
			//{
			//	bool bVerifyConsistency = false;
			//	if (InData->SkillType.TargetType == ESkillTargetType::FRIENDLY_FORCES)
			//	{
			//		bVerifyConsistency = InstigatorCharacter->GetTeamType() == OtherCharacter->GetTeamType();
			//	}
			//	else if (InData->SkillType.TargetType == ESkillTargetType::ENEMY)
			//	{
			//		bVerifyConsistency = InstigatorCharacter->GetTeamType() != OtherCharacter->GetTeamType();
			//	}

			//	return bVerifyConsistency;
			//};
			
			
			//是否 敌对队伍
			if (InstigatorCharacter != OtherCharacter)//InstigatorCharacter->IsTeam != OtherCharacter->IsTeam
			{
				//存活
				if (OtherCharacter->IsActive())
				{
					//生成伤害特效
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DamageParticle, GetActorLocation());//SweepResult.Location会返回0 

					//区分伤害类型	//根据类型决定 命中后是否销毁
					
					switch (BulletType)
					{
					case EBulletType::BULLET_NONE:																//不产生任何效果
					case EBulletType::BULLET_DIRECT_LINE:														//无障碍直线攻击，穿透
					case EBulletType::BULLET_LINE:																//非跟踪类型，类子弹；
					case EBulletType::BULLET_TRACK_LINE:														//跟踪类型
					case EBulletType::BULLET_TRACK_LINE_SP:														//跟踪类型
					{
						//应用伤害
						UGameplayStatics::ApplyDamage(
							OtherCharacter,
							100.f,
							InstigatorCharacter->GetController(),
							InstigatorCharacter,
							UDamageType::StaticClass());//伤害类型:默认

						//UClass* RuleOfTheDamage = URuleOfTheDamage::StaticClass();
						//if (URuleOfTheDamage* DamageClass = RuleOfTheDamage->GetDefaultObject<URuleOfTheDamage>())
						//{
						//	DamageClass->SkillData = InData;

						//	UGameplayStatics::ApplyDamage(
						//		OtherCharacter,
						//		100.f,
						//		InstigatorCharacter->GetController(),
						//		InstigatorCharacter,
						//		RuleOfTheDamage);
						//	//UDamageType::StaticClass());//伤害类型:默认
						//	
						//		

						//	//提交数据中心
						//	SubmissionSkillRequest();
						//}

						Destroy();
						break;
					}
						
					case EBulletType::BULLET_RANGE_THROW:														//范围伤害，丢手雷；
						
					{
						//应用范围伤害
						RadialDamage(OtherCharacter->GetActorLocation(), InstigatorCharacter);

						Destroy();
						break;
					}
					case EBulletType::BULLET_RANGE:																//范围伤害，类似自爆；
						break;
					case EBulletType::BULLET_CHAIN:																//链条类型，持续伤害类型;
						break;


					default:
						break;
					}

				}

				//先不管 统一销毁
				Destroy();

			}
		}
	}
}

//范围爆炸
void ARuleOfTheBullet::RadialDamage(const FVector& Origin, ARuleOfTheCharacter* InstigatorCharacter)
{


#if 1
	//if发射者
	if (InstigatorCharacter)
	{

		if (const FSkillData* InData = GetSkillData())
		{
			auto SpawnEffect = [&](ARuleOfTheCharacter* NewCharacter)
			{
				//生成伤害特效
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DamageParticle, NewCharacter->GetActorLocation());

				////提交技能请求
				//SubmissionSkillRequest();
			};








			//获取所有友军(忽略伤害)
			TArray<AActor*> IgnoreActors;
			//TArray<ARuleOfTheCharacter *> TargetActors;

			//遍历所有角色
			//判断 "发射者" 和 "目标" 是否是 相同队伍
			for (TActorIterator<ARuleOfTheCharacter>it(GetWorld(), ARuleOfTheCharacter::StaticClass()); it; ++it)
			{
				if (ARuleOfTheCharacter* TheCharacter = *it)
				{
					/*FVector VDistance = TheCharacter->GetActorLocation() - InstigatorCharacter->GetActorLocation();
					if (VDistance.Size() <= InData->AttackRange)
					{
						if (InData->SkillType.TargetType == ESkillTargetType::FRIENDLY_FORCES)
						{
							if (TheCharacter->GetTeamType() == InstigatorCharacter->GetTeamType())
							{
								SpawnEffect(TheCharacter);
							}
							else
							{
								IgnoreActors.Add(TheCharacter);
							}
						}
						else if (InData->SkillType.TargetType == ESkillTargetType::ENEMY)
						{
							if (TheCharacter->GetTeamType() != InstigatorCharacter->GetTeamType())
							{
								SpawnEffect(TheCharacter);
							}
							else
							{
								IgnoreActors.Add(TheCharacter);
							}
						}
					}*/
				}
			}

			/*UClass* RuleOfTheDamage = URuleOfTheDamage::StaticClass();
			if (URuleOfTheDamage* DamageClass = RuleOfTheDamage->GetDefaultObject<URuleOfTheDamage>())
			{
				DamageClass->SkillData = InData;*/

				/// <summary>
				/// 应用半径伤害
				/// </summary>																			 
				/// <param name="WorldContextObject"></param>		//getworld							
				/// <param name="BaseDamage"></param>				//基础伤害							
				/// <param name="MinimumDamage"></param>			//最小伤害							
				/// <param name="Origin"></param>					//中心位置							
				/// <param name="DamageInnerRadius"></param>		//伤害内半径							
				/// <param name="DamageOuterRadius"></param>		//伤害外半径							
				/// <param name="DamageFalloff"></param>			//衰减指数							
				/// <param name="DamageTypeClass"></param>			//伤害类型							
				/// <param name="IgnoreActors"></param>				//忽略Actor							 
				/// <param name="DamageCauser"></param>				//伤害来源							
				/// <param name="InstigatedByController"></param>	//伤害来源Controller
				/// <param name="DamagePreventionChannel"></param>	
				/// <returns></returns>
				UGameplayStatics::ApplyRadialDamageWithFalloff(
					GetWorld(),
					100.f, 10.f,
					Origin,
					400.f, 1000.f, .1f,
					UDamageType::StaticClass(), //伤害类型:默认
					//RuleOfTheDamage,
					IgnoreActors,
					GetInstigator(),
					GetInstigator()->GetController(),
					ECollisionChannel::ECC_MAX);//无视掩体


			//}
		}
	}


#endif // 0

	
	

}

void ARuleOfTheBullet::ChainAttack()
{
	
	if (ChainAttackHandle.IsValid())
	{

	}

	//主要伤害区
	if (1)//const FSkillData* InData = GetSkillData())
	{
		if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(GetInstigator()))
		{
			if (ARuleOfTheAIController* InstigatorController = Cast<ARuleOfTheAIController>(InstigatorCharacter->GetController()))
			{
				if (ARuleOfTheCharacter* TargetCharacter = InstigatorController->Target.Get())
				{
					////好像重复了
					//UGameplayStatics::SpawnEmitterAttached(OpenFireParticle, InstigatorCharacter->GetHommingPoint());
					//UGameplayStatics::SpawnEmitterAttached(DamageParticle, TargetCharacter->GetHommingPoint());

					/*UClass* RuleOfTheDamage = URuleOfTheDamage::StaticClass();
					if (URuleOfTheDamage* DamageClass = RuleOfTheDamage->GetDefaultObject<URuleOfTheDamage>())
					{
						DamageClass->SkillData = InData;

						UGameplayStatics::ApplyDamage(
							TargetCharacter,
							100.f,
							InstigatorCharacter->GetController(),
							InstigatorCharacter,
							RuleOfTheDamage);
					}*/


					//暂时用这个
					//
					//
					UGameplayStatics::ApplyDamage(
						TargetCharacter,
						100.f,
						InstigatorCharacter->GetController(),
						InstigatorCharacter,
						UDamageType::StaticClass());//伤害类型:默认

				}
			}
		}
	}

	ChainAttackCount--;
	if (ChainAttackCount <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(ChainAttackHandle);
	}
	
	

}





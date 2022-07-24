// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Bullet/RuleOfTheBullet.h"
#include "Particles/ParticleSystemComponent.h"//������Ч
#include "Components/SphereComponent.h"//�������
#include "GameFramework/ProjectileMovementComponent.h"//���������


#include "Character/Core/RuleOfTheCharacter.h"
#include "Kismet/GameplayStatics.h"				//��Ч
//#include "GameFramework/DamageType.h"
#include "Character/AIController/RuleOfTheAIController.h"
#include "EngineUtils.h"						//ʹ�õ����� ����
#include "Components/ArrowComponent.h"			//��ȡ�����
#include "Components/SplineComponent.h"			//׷��·��
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
	ProjectileMovement->ProjectileGravityScale = 0.f;		//����0
	ProjectileMovement->UpdatedComponent = BoxDamage;		
	BulletType = EBulletType::BULLET_NONE;					//Ĭ���ӵ�����

	//SubmissionSkillRequestType = ESubmissionSkillRequestType::AUTO;
	
	InitialLifeSpan = 4.0f;									//4����Զ�����
}

// Called when the game starts or when spawned
void ARuleOfTheBullet::BeginPlay()
{
	Super::BeginPlay();
	//�� BoxDamage��ʼ�ص� ������
	BoxDamage->OnComponentBeginOverlap.AddUniqueDynamic(this, &ARuleOfTheBullet::BeginOverlap);

	InitSkill();

}

// Called every frame
void ARuleOfTheBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	//������֡��ʾ�Ĺ�����ʽ
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
						//SceneComponent����
						TArray<USceneComponent*> SceneComponent;
						//��ȡ��������Component (�Ƿ������������, ����)
						RootComponent->GetChildrenComponents(true, SceneComponent);
						//����
						for (auto& Tmp : SceneComponent)
						{
							if (UParticleSystemComponent* ParticleSystem = Cast<UParticleSystemComponent>(Tmp))
							{
								//����ԭ�� Ŀ���
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
							//..ˢ��׷�ٵ�
							Spline->RemoveSplinePoint(2);
							Spline->AddSplinePoint(TargetCharacter->GetActorLocation(), ESplineCoordinateSpace::Local);
							

							FVector DistanceVector = TargetCharacter->GetActorLocation() - InstigatorCharacter->GetActorLocation();
							CurrentSplineTime += DeltaTime;
							/// <summary>
							///							 ����ʱ��							����ʱ��
							/// �߹��ľ��� = ·������ * ______________	 = ·������ * _____________________
							///							��������ʱ��						(ֱ�߾���/��ʼ�ٶ�)
							/// </summary>
							float DistanceTraveled = Spline->GetSplineLength() * (CurrentSplineTime / (DistanceVector.Size() / ProjectileMovement->InitialSpeed));
							//ͨ���߹��ľ��� ���λ�ú���ת
							FVector Loction = Spline->GetWorldLocationAtDistanceAlongSpline(DistanceTraveled);
							FRotator Rotator = Spline->GetRotationAtDistanceAlongSpline(DistanceTraveled, ESplineCoordinateSpace::Local);

							SetActorLocationAndRotation(Loction, Rotator);

							//�ӽ�target
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
/// ��ʼ�����ӵ�����
/// </summary>
void ARuleOfTheBullet::InitSkill()
{
	//��ȡ ������
	if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(GetInstigator()))
	{
		//��ȡ ������Controller
		if (ARuleOfTheAIController* InstigatorController = Cast<ARuleOfTheAIController>(InstigatorCharacter->GetController()))
		{
			//��ȡ Ŀ��
			if (ARuleOfTheCharacter* TargetCharacter = InstigatorController->Target.Get())
			{
				//ǹ����Ч
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OpenFireParticle, GetActorLocation());

				switch (BulletType)
				{
				case EBulletType::BULLET_NONE:																//�������κ�Ч��
					break;
				case EBulletType::BULLET_DIRECT_LINE:														//ֱ�߹�������͸
					break;
				case EBulletType::BULLET_LINE:																//ֱ�߹���������͸��
					break;
				case EBulletType::BULLET_TRACK_LINE:														//��������
					ProjectileMovement->bIsHomingProjectile = true;//�Ƿ����
					ProjectileMovement->bRotationFollowsVelocity = true;//��ת�����˶�
					ProjectileMovement->HomingAccelerationMagnitude = 8000.f;//���ٶ�
					ProjectileMovement->HomingTargetComponent = TargetCharacter->GetHommingPoint(); //�������
					break;
				case EBulletType::BULLET_TRACK_LINE_SP:														//��������SPline
				{
					ProjectileMovement->StopMovementImmediately();

					//���� && ע�����
					Spline = NewObject<USplineComponent>(this, TEXT("SplineInstance"));
					Spline->RegisterComponent();

					//Instigator��target ���ĵ����� && ���� && ƫ�� && �߶�
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
					
					//index 0, ��ʼλ��, 
					Spline->SetLocationAtSplinePoint(0, GetActorLocation(), ESplineCoordinateSpace::Local);
					//index 1, ·��λ��
					Spline->SetLocationAtSplinePoint(1, Position, ESplineCoordinateSpace::Local);
					//���Targetλ��(��Tick�и���λ��)
					Spline->AddSplinePoint(TargetCharacter->GetActorLocation(), ESplineCoordinateSpace::Local);
					break;
				}
				case EBulletType::BULLET_RANGE_THROW:														//��Χ�˺��������ף�
				{
					ProjectileMovement->StopMovementImmediately();
					
					ProjectileMovement->ProjectileGravityScale = 3.f;

					///// <summary>
					/////					 (180 / PI) * Asin[ (Distance*-g) / (v*v) ] 
					///// ����Ƕ�()  = 90 - ____________________________________________
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
					
				case EBulletType::BULLET_RANGE:																//��Χ�˺����ӵ����䣻
					ProjectileMovement->StopMovementImmediately();//ֹͣ�ƶ�
					BoxDamage->SetCollisionEnabled(ECollisionEnabled::NoCollision);//�����ײ
					RadialDamage(GetActorLocation(), Cast<ARuleOfTheCharacter>(GetInstigator()));//Ӧ��Բ�η�Χ�˺�

					break;
				case EBulletType::BULLET_CHAIN:																//�������ͣ������˺�����;
				{
					ProjectileMovement->StopMovementImmediately();
					BoxDamage->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					//������Ч�󶨵�target
					UGameplayStatics::SpawnEmitterAttached(OpenFireParticle, InstigatorCharacter->GetHommingPoint());
					UGameplayStatics::SpawnEmitterAttached(DamageParticle, TargetCharacter->GetHommingPoint());
					//Ӧ�ó����˺�
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





/// ���з���
void ARuleOfTheBullet::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (const FSkillData* InData = GetSkillData()){}
	
	//��� ������
	if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(GetInstigator()))
	{
		//��� ����Ŀ��
		if (ARuleOfTheCharacter* OtherCharacter = Cast<ARuleOfTheCharacter>(OtherActor))
		{
			////��ʱ����  �ж� ��ͬ����
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
			
			
			//�Ƿ� �жԶ���
			if (InstigatorCharacter != OtherCharacter)//InstigatorCharacter->IsTeam != OtherCharacter->IsTeam
			{
				//���
				if (OtherCharacter->IsActive())
				{
					//�����˺���Ч
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DamageParticle, GetActorLocation());//SweepResult.Location�᷵��0 

					//�����˺�����	//�������;��� ���к��Ƿ�����
					
					switch (BulletType)
					{
					case EBulletType::BULLET_NONE:																//�������κ�Ч��
					case EBulletType::BULLET_DIRECT_LINE:														//���ϰ�ֱ�߹�������͸
					case EBulletType::BULLET_LINE:																//�Ǹ������ͣ����ӵ���
					case EBulletType::BULLET_TRACK_LINE:														//��������
					case EBulletType::BULLET_TRACK_LINE_SP:														//��������
					{
						//Ӧ���˺�
						UGameplayStatics::ApplyDamage(
							OtherCharacter,
							100.f,
							InstigatorCharacter->GetController(),
							InstigatorCharacter,
							UDamageType::StaticClass());//�˺�����:Ĭ��

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
						//	//UDamageType::StaticClass());//�˺�����:Ĭ��
						//	
						//		

						//	//�ύ��������
						//	SubmissionSkillRequest();
						//}

						Destroy();
						break;
					}
						
					case EBulletType::BULLET_RANGE_THROW:														//��Χ�˺��������ף�
						
					{
						//Ӧ�÷�Χ�˺�
						RadialDamage(OtherCharacter->GetActorLocation(), InstigatorCharacter);

						Destroy();
						break;
					}
					case EBulletType::BULLET_RANGE:																//��Χ�˺��������Ա���
						break;
					case EBulletType::BULLET_CHAIN:																//�������ͣ������˺�����;
						break;


					default:
						break;
					}

				}

				//�Ȳ��� ͳһ����
				Destroy();

			}
		}
	}
}

//��Χ��ը
void ARuleOfTheBullet::RadialDamage(const FVector& Origin, ARuleOfTheCharacter* InstigatorCharacter)
{


#if 1
	//if������
	if (InstigatorCharacter)
	{

		if (const FSkillData* InData = GetSkillData())
		{
			auto SpawnEffect = [&](ARuleOfTheCharacter* NewCharacter)
			{
				//�����˺���Ч
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DamageParticle, NewCharacter->GetActorLocation());

				////�ύ��������
				//SubmissionSkillRequest();
			};








			//��ȡ�����Ѿ�(�����˺�)
			TArray<AActor*> IgnoreActors;
			//TArray<ARuleOfTheCharacter *> TargetActors;

			//�������н�ɫ
			//�ж� "������" �� "Ŀ��" �Ƿ��� ��ͬ����
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
				/// Ӧ�ð뾶�˺�
				/// </summary>																			 
				/// <param name="WorldContextObject"></param>		//getworld							
				/// <param name="BaseDamage"></param>				//�����˺�							
				/// <param name="MinimumDamage"></param>			//��С�˺�							
				/// <param name="Origin"></param>					//����λ��							
				/// <param name="DamageInnerRadius"></param>		//�˺��ڰ뾶							
				/// <param name="DamageOuterRadius"></param>		//�˺���뾶							
				/// <param name="DamageFalloff"></param>			//˥��ָ��							
				/// <param name="DamageTypeClass"></param>			//�˺�����							
				/// <param name="IgnoreActors"></param>				//����Actor							 
				/// <param name="DamageCauser"></param>				//�˺���Դ							
				/// <param name="InstigatedByController"></param>	//�˺���ԴController
				/// <param name="DamagePreventionChannel"></param>	
				/// <returns></returns>
				UGameplayStatics::ApplyRadialDamageWithFalloff(
					GetWorld(),
					100.f, 10.f,
					Origin,
					400.f, 1000.f, .1f,
					UDamageType::StaticClass(), //�˺�����:Ĭ��
					//RuleOfTheDamage,
					IgnoreActors,
					GetInstigator(),
					GetInstigator()->GetController(),
					ECollisionChannel::ECC_MAX);//��������


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

	//��Ҫ�˺���
	if (1)//const FSkillData* InData = GetSkillData())
	{
		if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(GetInstigator()))
		{
			if (ARuleOfTheAIController* InstigatorController = Cast<ARuleOfTheAIController>(InstigatorCharacter->GetController()))
			{
				if (ARuleOfTheCharacter* TargetCharacter = InstigatorController->Target.Get())
				{
					////�����ظ���
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


					//��ʱ�����
					//
					//
					UGameplayStatics::ApplyDamage(
						TargetCharacter,
						100.f,
						InstigatorCharacter->GetController(),
						InstigatorCharacter,
						UDamageType::StaticClass());//�˺�����:Ĭ��

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





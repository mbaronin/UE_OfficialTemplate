// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Resources/Core/TDGameResources.h"//ö��
#include "Business_process_2\EnumType.h"

#include "RuleOfTheBullet.generated.h"

class ARuleOfTheCharacter;
class USplineComponent;
struct FSkillData;
UCLASS()
class BUSINESS_PROCESS_2_API ARuleOfTheBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARuleOfTheBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	const FSkillData* GetSkillData();
public:
	//��ײ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* BoxDamage;

	//��Ϊ�����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* RootBullet;

	//�����ƶ����Ե����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

	//�ӵ����˺���Ч(��ײ���������Ч)
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		UParticleSystem* DamageParticle;
	
	//������Ч
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		UParticleSystem* OpenFireParticle;

	//�ӵ�����
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		TEnumAsByte<EBulletType> BulletType;

	//��ʼ�� �ӵ�����
	void InitSkill();


	//���м��
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	//Բ�η�Χ�˺�
	void RadialDamage(const FVector& Origin, ARuleOfTheCharacter* InstigatorCharacter);
	
	UFUNCTION()
		void ChainAttack();


	//׷��ƫ��ֵ
	UPROPERTY(EditDefaultsOnly, Category = "Bullet track line sp")
		float SplineOffsetHorizontal;
	UPROPERTY(EditDefaultsOnly, Category = "Bullet track line sp")
		float SplineOffsetVertical;
	UPROPERTY(EditDefaultsOnly, Category = "Bullet track line sp")
		bool AutoSplineOffset;
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		int32 SkillID;

private:
	//����·��
	UPROPERTY()
		USplineComponent* Spline;
	//����ʱ��
	UPROPERTY()
		float CurrentSplineTime;

	FTimerHandle ChainAttackHandle;

	UPROPERTY()
		uint8 ChainAttackCount;


};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Resources/Core/TDGameResources.h"//枚举
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
	//碰撞盒子
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* BoxDamage;

	//作为根组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* RootBullet;

	//具有移动属性的组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

	//子弹的伤害特效(碰撞后产生的特效)
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		UParticleSystem* DamageParticle;
	
	//开火特效
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		UParticleSystem* OpenFireParticle;

	//子弹分类
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		TEnumAsByte<EBulletType> BulletType;

	//初始化 子弹类型
	void InitSkill();


	//命中检测
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	//圆形范围伤害
	void RadialDamage(const FVector& Origin, ARuleOfTheCharacter* InstigatorCharacter);
	
	UFUNCTION()
		void ChainAttack();


	//追踪偏移值
	UPROPERTY(EditDefaultsOnly, Category = "Bullet track line sp")
		float SplineOffsetHorizontal;
	UPROPERTY(EditDefaultsOnly, Category = "Bullet track line sp")
		float SplineOffsetVertical;
	UPROPERTY(EditDefaultsOnly, Category = "Bullet track line sp")
		bool AutoSplineOffset;
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		int32 SkillID;

private:
	//导航路径
	UPROPERTY()
		USplineComponent* Spline;
	//生成时间
	UPROPERTY()
		float CurrentSplineTime;

	FTimerHandle ChainAttackHandle;

	UPROPERTY()
		uint8 ChainAttackCount;


};

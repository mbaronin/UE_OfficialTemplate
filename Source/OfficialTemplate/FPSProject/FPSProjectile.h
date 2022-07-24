// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSProjectile.generated.h"

UCLASS()
class OFFICIALTEMPLATE_API AFPSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSProjectile();
	
	
	// 球体碰撞组件。
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent* CollisionComponent;

	// 发射物移动组件。
	UPROPERTY(VisibleAnywhere, Category = Movement)
		class UProjectileMovementComponent* ProjectileMovementComponent;

	// 发射物网格体
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		UStaticMeshComponent* ProjectileMeshComponent;

	// 发射物材质
	UPROPERTY(VisibleDefaultsOnly, Category = Movement)
		UMaterialInstanceDynamic* ProjectileMaterialInstance;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 初始化射击方向上发射物速度的函数。
	void FireInDirection(const FVector& ShootDirection);
	// 当发射物击中物体时会调用的函数。

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
};

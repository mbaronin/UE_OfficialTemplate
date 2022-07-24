// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
////////
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "FPSProjectile.h"

#include "FPSCharacter.generated.h"

UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// 要生成的发射物类。
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// 处理用于前后移动的输入。
	UFUNCTION()
		void MoveForward(float Value);

	// 处理用于左右移动的输入。
	UFUNCTION()
		void MoveRight(float Value);

	// 按下键时，设置跳跃标记。
	UFUNCTION()
		void StartJump();

	// 释放键时，清除跳跃标记。
	UFUNCTION()
		void StopJump();

	// FPS摄像机。
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;

	// 第一人称网格体（手臂），仅对所属玩家可见。
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* FPSMesh;

	// 处理发射物射击的函数。
	UFUNCTION()
		void Fire();

	// 枪口相对于摄像机位置的偏移。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	


};

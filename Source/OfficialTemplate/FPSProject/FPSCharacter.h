// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "FPSProject/FPSProjectile.h"

#include "FPSCharacter.generated.h"
UCLASS()
class OFFICIALTEMPLATE_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

	// FPS摄像机。
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* FPSCameraComponent;

	// 第一人称网格体（手臂），仅对所属玩家可见。
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* FPSMesh;

	// 枪口相对于摄像机位置的偏移。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// 要生成的发射物类。
	UPROPERTY(EditAnywhere, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void MoveForward(float Value);
	void MoveRight(float Value);

	//UFUNCTION()
	void StartJump();
	void StopJump();

	// 处理发射物射击的函数。
	void Fire();

};

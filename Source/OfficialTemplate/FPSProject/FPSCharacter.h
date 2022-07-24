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

	// FPS�������
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* FPSCameraComponent;

	// ��һ�˳������壨�ֱۣ�������������ҿɼ���
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* FPSMesh;

	// ǹ������������λ�õ�ƫ�ơ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Ҫ���ɵķ������ࡣ
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

	// ������������ĺ�����
	void Fire();

};

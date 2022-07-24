// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnWithCamera.generated.h"

UCLASS()
class OFFICIALTEMPLATE_API APawnWithCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnWithCamera();

	//// 材质
	//UPROPERTY(EditAnywhere, Category = Movement)
	//	UMaterialInstanceDynamic* MaterialInstance;

	UPROPERTY(EditAnywhere)
		class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

	

	//输入变量
	FVector2D MovementInput;
	FVector2D CameraInput;
	float ZoomFactor;
	bool bZoomingIn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 输入函数
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);
	void ZoomIn();
	void ZoomOut();

};

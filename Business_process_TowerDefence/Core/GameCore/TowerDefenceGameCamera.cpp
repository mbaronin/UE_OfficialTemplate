// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameCore/TowerDefenceGameCamera.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"



// Sets default values
ATowerDefenceGameCamera::ATowerDefenceGameCamera():
	SpringArmLength(2000.0)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/////////���� ���ɱ� ����� ��ײ����
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Boom"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main_Camera"));
	MarkBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Sign"));
	//////���ӵ������
	CameraBoom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	MainCamera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform);
	MarkBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	/////////���ɱ۳�����Ƕ�
	CameraBoom->TargetArmLength = SpringArmLength;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));

	//�رյ��ɱ���ײ
	CameraBoom->bDoCollisionTest = false;

}

// Called when the game starts or when spawned
void ATowerDefenceGameCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATowerDefenceGameCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATowerDefenceGameCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//��Ұ����
void ATowerDefenceGameCamera::Zoom(bool Direction, const float& ZoomSpeed)
{
	if (Direction)
	{
		if (CameraBoom->TargetArmLength > 400)
		{
			CameraBoom->TargetArmLength -= ZoomSpeed;
		}
	}
	else
	{
		if (CameraBoom->TargetArmLength < SpringArmLength)
		{
			CameraBoom->TargetArmLength += ZoomSpeed;
		}
	}
}

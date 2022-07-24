// Fill out your copyright notice in the Description page of Project Settings.


#include "HowTo_Components/CollidingPawn.h"
#include "HowTo_Components/CollidingPawnMovementComponent.h"

#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"//΢��ϵͳ
#include "Components/SphereComponent.h"//����
#include "Camera/CameraComponent.h"//�����
#include "GameFramework/SpringArmComponent.h"//���ɱ�

// Sets default values
ACollidingPawn::ACollidingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���������Ϊ������Ӧ������
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	// ����������������������Ա�鿴����λ��
	/*UStaticMeshComponent**/ SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/HowTo_Components/Sphere_Pawn.Sphere_Pawn")); 
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		SphereVisual->SetWorldScale3D(FVector(1.0f));
	}

	// �����ɼ����ֹͣ������ϵͳ
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(SphereVisual);
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}

	// ʹ�õ��ɱ۸��������ƽ����Ȼ���˶��С�
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	// ��������������ӵ����ɱ�
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// ����Ĭ�����
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// �����ƶ������ʵ������Ҫ������¸���
	OurMovementComponent = CreateDefaultSubobject<UCollidingPawnMovementComponent>(TEXT("CustomMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;




}

// Called when the game starts or when spawned
void ACollidingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollidingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ����"Grow"������������������
	{
		float CurrentScale = SphereVisual->GetComponentScale().X;
		if (bGrowing)
		{
			// һ����������������С
			CurrentScale += DeltaTime;
		}
		else
		{
			// �������ٶ�����һ��
			CurrentScale -= (DeltaTime * 0.2f);
		}
		// ȷ�����ή����ʼ��С���£���������������С���ϡ�
		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
		SphereVisual->SetWorldScale3D(FVector(CurrentScale));
	}




}

// Called to bind functionality to input
void ACollidingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACollidingPawn::ParticleToggle);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACollidingPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACollidingPawn::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACollidingPawn::Turn);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ACollidingPawn::StartGrowing);
	PlayerInputComponent->BindAction("ResetVR", IE_Released, this, &ACollidingPawn::StopGrowing);

}

UPawnMovementComponent* ACollidingPawn::GetMovementComponent() const
{
	return OurMovementComponent;
}

void ACollidingPawn::MoveForward(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void ACollidingPawn::MoveRight(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

void ACollidingPawn::Turn(float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
}

void ACollidingPawn::ParticleToggle()
{
	if (OurParticleSystem && OurParticleSystem->Template)
	{
		OurParticleSystem->ToggleActive();
	}
}


void ACollidingPawn::StartGrowing()
{
	bGrowing = true;
}

void ACollidingPawn::StopGrowing()
{
	bGrowing = false;
}
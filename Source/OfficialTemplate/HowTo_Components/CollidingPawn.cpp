// Fill out your copyright notice in the Description page of Project Settings.


#include "HowTo_Components/CollidingPawn.h"
#include "HowTo_Components/CollidingPawnMovementComponent.h"

#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"//微粒系统
#include "Components/SphereComponent.h"//球体
#include "Camera/CameraComponent.h"//摄像机
#include "GameFramework/SpringArmComponent.h"//弹簧臂

// Sets default values
ACollidingPawn::ACollidingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 根组件将成为对物理反应的球体
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	// 创建并放置网格体组件，以便查看球体位置
	/*UStaticMeshComponent**/ SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/HowTo_Components/Sphere_Pawn.Sphere_Pawn")); 
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		SphereVisual->SetWorldScale3D(FVector(1.0f));
	}

	// 创建可激活或停止的粒子系统
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(SphereVisual);
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}

	// 使用弹簧臂给予摄像机平滑自然的运动感。
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	// 创建摄像机并附加到弹簧臂
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// 控制默认玩家
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// 创建移动组件的实例，并要求其更新根。
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

	// 根据"Grow"操作处理增长和缩减
	{
		float CurrentScale = SphereVisual->GetComponentScale().X;
		if (bGrowing)
		{
			// 一秒内增长到两倍大小
			CurrentScale += DeltaTime;
		}
		else
		{
			// 以增长速度缩减一半
			CurrentScale -= (DeltaTime * 0.2f);
		}
		// 确保不会降至初始大小以下，或者增至两倍大小以上。
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
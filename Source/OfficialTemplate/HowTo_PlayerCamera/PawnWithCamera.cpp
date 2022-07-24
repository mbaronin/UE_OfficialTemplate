// Fill out your copyright notice in the Description page of Project Settings.


#include "HowTo_PlayerCamera/PawnWithCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
APawnWithCamera::APawnWithCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//创建组件
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	//绑定组件
	StaticMeshComp->SetupAttachment(RootComponent);
	SpringArmComp->SetupAttachment(StaticMeshComp);
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/HowTo_Components/Sphere_Pawn.Sphere_Pawn"));
	if (SphereVisualAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(SphereVisualAsset.Object);
		StaticMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		StaticMeshComp->SetWorldScale3D(FVector(1.0f));
	}

	//// 材质/尺寸
	//static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("Material'/Game/FPSProject/Projectile/ProjectileMaterial.ProjectileMaterial'"));
	//if (Material.Succeeded())
	//{
	//	MaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, StaticMeshComp);
	//}
	//StaticMeshComp->SetMaterial(0, MaterialInstance);



	//为SpringArm类的变量赋值。
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	SpringArmComp->TargetArmLength = 400.f;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 3.0f;

	//控制默认玩家
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void APawnWithCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//如果按下了放大按钮则放大，否则就缩小
	{
		if (bZoomingIn)
		{
			ZoomFactor += DeltaTime / 0.5f;         //Zoom in over half a second
		}
		else
		{
			ZoomFactor -= DeltaTime / 0.25f;        //Zoom out over a quarter of a second
		}
		ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);

		//根据ZoomFactor来设置摄像机的视场和弹簧臂的长度
		CameraComp->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
		SpringArmComp->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);
	}



	// 旋转Actor的偏转角度，由于摄像机与Actor相互绑定，因此摄像机也会偏转
	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += CameraInput.X;
		SetActorRotation(NewRotation);
	}

	// 旋转摄像机的俯仰角度，但对其进行限制，确保我们始终朝下看
	{
		FRotator NewRotation = SpringArmComp->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
		SpringArmComp->SetWorldRotation(NewRotation);
	}

	// 根据"MoveX"和"MoveY"的处理移动
	{
		if (!MovementInput.IsZero())
		{
			// 把移动轴的输入数值放大100倍
			MovementInput = MovementInput.GetSafeNormal() * 100.0f;
			FVector NewLocation = GetActorLocation();
			NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
			NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
			SetActorLocation(NewLocation);
		}
	}


}

// Called to bind functionality to input
void APawnWithCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 绑定"ZoomIn"的事件
	InputComponent->BindAction("RButton", IE_Pressed, this, &APawnWithCamera::ZoomIn);
	InputComponent->BindAction("RButton", IE_Released, this, &APawnWithCamera::ZoomOut);

	//为四条轴绑定事件（每帧调用）
	InputComponent->BindAxis("MoveForward", this, &APawnWithCamera::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APawnWithCamera::MoveRight);
	InputComponent->BindAxis("LookUp", this, &APawnWithCamera::PitchCamera);
	InputComponent->BindAxis("Turn", this, &APawnWithCamera::YawCamera);

}

// 输入函数
void APawnWithCamera::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnWithCamera::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnWithCamera::PitchCamera(float AxisValue)
{
	CameraInput.Y = -AxisValue;
}

void APawnWithCamera::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void APawnWithCamera::ZoomIn()
{
	bZoomingIn = true;
}

void APawnWithCamera::ZoomOut()
{
	bZoomingIn = false;
}
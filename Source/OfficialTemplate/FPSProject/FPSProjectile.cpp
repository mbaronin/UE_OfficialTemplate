// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject/FPSProjectile.h"
#include "Components/SphereComponent.h"//球体碰撞
#include "GameFramework/ProjectileMovementComponent.h"//发射物


// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;





	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	

	// 球体碰撞组件。
	if (!CollisionComponent)
	{
		// 用球体进行简单的碰撞展示。
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// 将球体的碰撞配置文件名称设置为"Projectile"。
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
		// 组件击中某物时调用的事件。
		CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);
		// 设置球体的碰撞半径。
		CollisionComponent->InitSphereRadius(15.0f);
		// 将根组件设置为碰撞组件。
		RootComponent = CollisionComponent;
	}

	// 发射物移动组件。
	if (!ProjectileMovementComponent)
	{
		// 使用此组件驱动发射物的移动。
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	// 发射物网格体
	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/FPSProject/Projectile/Projectile.Projectile'"));
		if (Mesh.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
			
		}
	}

	// 发射物材质/尺寸
	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("Material'/Game/FPSProject/Projectile/ProjectileMaterial.ProjectileMaterial'"));
	if (Material.Succeeded())
	{
		ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
	}
	ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
	//ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
	ProjectileMeshComponent->SetRelativeScale3D(FVector(1.00f, 1.00f, 1.00f));
	ProjectileMeshComponent->SetupAttachment(RootComponent);


	

	// 3 秒后删除发射物。
	InitialLifeSpan = 3.0f;

}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;

}

void AFPSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{

	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}

	Destroy();

}




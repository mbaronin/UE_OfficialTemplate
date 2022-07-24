// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterCore/Towers.h"
#include "Components/StaticMeshComponent.h"
#include "DestructibleComponent.h"//��Ҫ��build�ļ��а��� �������������
//#include "F:\ue\UE_4.27\Engine\Plugins\Runtime\ApexDestruction\Source\ApexDestruction\Public\DestructibleComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "Global/UI_Datas.h"


ATowers::ATowers()

{
	////����ģ�� Ԥ��ģ�� �ƻ�Ч��
	//ParticleMesh = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleMesh"));
	//StaticMeshBuilding = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RangeBuilding"));
	//DestructibleMeshBuilding = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Subsitute"));

	////�󶨵������
	//StaticMeshBuilding->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);//�������λ�ò���
	//DestructibleMeshBuilding->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//ParticleMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}


void ATowers::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}


float ATowers::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

    return 0.0f;
}

ECharacterType ATowers::GetCharacterType()
{
	return ECharacterType::TOWER;
}

void ATowers::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	Super::OnClicked(TouchedComponent, ButtonPressed);

	if (ClickedTargetTower == nullptr)
	{
		ClickedTargetTower = this;
	}
	else
	{
		ClickedTargetTower = nullptr;
	}
}

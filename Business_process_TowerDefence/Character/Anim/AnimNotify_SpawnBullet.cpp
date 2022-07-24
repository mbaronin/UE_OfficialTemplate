// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Anim/AnimNotify_SpawnBullet.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "Character/Bullet/RuleOfTheBullet.h"
#include "Components/SkeletalMeshComponent.h"//�������
#include "Components/ArrowComponent.h"
#include "Business_process_2/FunctionUtils.h"


UAnimNotify_SpawnBullet::UAnimNotify_SpawnBullet()
	:Super()
{
// WITH_EDITORONLY_DATA
#if WITH_EDITORONLY_DATA
	InSocketName = TEXT("OpenFire");
	NotifyColor = FColor(196, 142, 255, 255);
#endif 
}

//FString UAnimNotify_SpawnBullet::GetNotifyName_Implementation() const
//{
//	if (BulletClass)
//	{
//		return BulletClass->GetName();
//	}
//	else
//	{
//		return Super::GetNotifyName_Implementation();
//	}
//}

void UAnimNotify_SpawnBullet::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//�ڶ���Ԥ����������ʾ&&����������ʾ
#if WITH_EDITOR
	FVector ComponentLocation = MeshComp->GetSocketLocation(InSocketName);
	FRotator ComponentRotation = MeshComp->GetSocketRotation(InSocketName);
#else
	FVector ComponentLocation = Character->GetFirePoint()->GetComponentLocation();
	FRotator ComponentRotation = Character->GetFirePoint()->GetComponentRotation();
#endif
	//����һ��λ��
	ComponentRotation.Pitch += 15.0f;


#if 1
//���� SkeletalMesh ��ȡCharacter
	if (AActor* Character = Cast<AActor>(MeshComp->GetOuter()))
	{
		//ģ��
		if (ARuleOfTheBullet* Bullet = FunctionUtils::SpawnBullet(Character->GetWorld(), Cast<APawn>(Character), BulletClass, ComponentLocation, ComponentRotation))
		{
			/*Bullet->SubmissionSkillRequestType = ESubmissionSkillRequestType::MANUAL;
			Bullet->InitSkill();*/
		}
	}
#else

	if (ARuleOfTheCharacter* Character = Cast<ARuleOfTheCharacter>(MeshComp->GetOuter()))
	{
		//�����ӵ� (����,��ת ,λ��)
		if (ARuleOfTheBullet* Bullet = Character->GetWorld()->SpawnActor<ARuleOfTheBullet>(BulletClass, ComponentLocation, ComponentRotation))
		{
			//�����ӵ�λ��(��ͷ���λ��)


		}
	}
#endif // 1

	
	 
	 
	


	
}
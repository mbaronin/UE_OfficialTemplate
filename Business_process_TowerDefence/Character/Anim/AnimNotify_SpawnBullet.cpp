// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Anim/AnimNotify_SpawnBullet.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "Character/Bullet/RuleOfTheBullet.h"
#include "Components/SkeletalMeshComponent.h"//骨骼组件
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
	//在动画预览界面中显示&&在运行中显示
#if WITH_EDITOR
	FVector ComponentLocation = MeshComp->GetSocketLocation(InSocketName);
	FRotator ComponentRotation = MeshComp->GetSocketRotation(InSocketName);
#else
	FVector ComponentLocation = Character->GetFirePoint()->GetComponentLocation();
	FRotator ComponentRotation = Character->GetFirePoint()->GetComponentRotation();
#endif
	//修正一下位置
	ComponentRotation.Pitch += 15.0f;


#if 1
//利用 SkeletalMesh 获取Character
	if (AActor* Character = Cast<AActor>(MeshComp->GetOuter()))
	{
		//模板
		if (ARuleOfTheBullet* Bullet = FunctionUtils::SpawnBullet(Character->GetWorld(), Cast<APawn>(Character), BulletClass, ComponentLocation, ComponentRotation))
		{
			/*Bullet->SubmissionSkillRequestType = ESubmissionSkillRequestType::MANUAL;
			Bullet->InitSkill();*/
		}
	}
#else

	if (ARuleOfTheCharacter* Character = Cast<ARuleOfTheCharacter>(MeshComp->GetOuter()))
	{
		//生成子弹 (类型,旋转 ,位置)
		if (ARuleOfTheBullet* Bullet = Character->GetWorld()->SpawnActor<ARuleOfTheBullet>(BulletClass, ComponentLocation, ComponentRotation))
		{
			//设置子弹位置(箭头组件位置)


		}
	}
#endif // 1

	
	 
	 
	


	
}
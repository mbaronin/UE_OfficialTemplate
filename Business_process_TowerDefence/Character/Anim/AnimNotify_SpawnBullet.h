// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SpawnBullet.generated.h"

class ARuleOfTheBullet;

/**
 * 
 */
UCLASS()
class BUSINESS_PROCESS_2_API UAnimNotify_SpawnBullet : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_SpawnBullet();

	// Begin UAnimNotify interface
	//virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (ExposeOnSpawn = true))
		TSubclassOf<ARuleOfTheBullet> BulletClass;

	//‘⁄±‡“Î∆˜÷–‘§¿¿œ‘ æ
#if WITH_EDITOR
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (ExposeOnSpawn = true))
		FName InSocketName;
#endif


};

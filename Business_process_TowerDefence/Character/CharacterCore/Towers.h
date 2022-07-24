// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "Towers.generated.h"


class UParticleSystemComponent;
class UStaticMeshComponent;
class UDestructibleComponent;
/**
 * 
 */
UCLASS()
class BUSINESS_PROCESS_2_API ATowers : public ARuleOfTheCharacter
{
	GENERATED_BODY()
	
public:
	////����ģ��
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
	//	UParticleSystemComponent* ParticleMesh;
	////��̬������ģ��
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
	//	UStaticMeshComponent* StaticMeshBuilding;
	////�ƻ���Чģ��
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
	//	UDestructibleComponent* DestructibleMeshBuilding;

	//��ת
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute")
		FRotator TowersRotator;

public:
	ATowers();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


public:
	virtual ECharacterType GetCharacterType() override;//?

	virtual void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

};

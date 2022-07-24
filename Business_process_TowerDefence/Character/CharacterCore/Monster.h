// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "Monster.generated.h"

/**
 * 
 */
UCLASS()
class BUSINESS_PROCESS_2_API AMonster : public ARuleOfTheCharacter
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual ECharacterType GetCharacterType() override;

	virtual void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterCore/Monster.h"

#include "Global/UI_Datas.h"


void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	////速度设定
	/*if (const FCharacterData* InCharacterData = GetCharacterData())
	{
		if (InCharacterData->IsValid())
		{
			GetCharacterMovement()->MaxWalkSpeed = InCharacterData->GetWalkSpeed();
		}
	}*/
}

ECharacterType AMonster::GetCharacterType()
{
	return ECharacterType::MONSTER;
}

void AMonster::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	Super::OnClicked(TouchedComponent, ButtonPressed);
	if (ClickedTargetMonster)
	{
		ClickedTargetMonster = nullptr;
	}
	else
	{
		ClickedTargetMonster = this;
	}
}


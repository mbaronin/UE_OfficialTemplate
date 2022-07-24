// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Business_process_2/FunctionUtils.h"

#include "TowerDefenceGameInstance.generated.h"




/**
 * 
 */
UCLASS()
class BUSINESS_PROCESS_2_API UTowerDefenceGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UTowerDefenceGameInstance();

	virtual void Init() override;



	int32 GetCurrentSaveSlotNumber() const;

	void ClearSaveMark();

	
	EGameSaveType GetGameType() { return GameSaveType; };

protected:
	UPROPERTY()
		int32 SaveSlotNumber;
	//ÓÎÏ·´æ´¢×´Ì¬flag
	EGameSaveType GameSaveType;
	
};

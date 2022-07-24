// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/GameState.h"
#include "GameFramework/GameStateBase.h"

#include "RuleOfTheGameState.generated.h"

/**
 * 
 */
class UGameSaveSlotList;
struct FSaveSlotList;
struct FSaveSlot;

UCLASS()
class BUSINESS_PROCESS_2_API ARuleOfTheGameState : public AGameStateBase//AGameState //会引起很严重的bug
{
	GENERATED_BODY()
	

public:
	ARuleOfTheGameState();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//在子类中重载
	UFUNCTION(BlueprintCallable, Category = SaveData)
		virtual	bool SaveGameData(int32 SaveNumber) { return false; }
	UFUNCTION(BlueprintCallable, Category = SaveData)
		virtual	bool ReadGameData(int32 SaveNumber) { return false; }

	virtual	bool ClearGameData(int32 SaveNumber);

	FSaveSlotList& GetSaveSlotList();

	

	virtual FSaveSlot* GetSaveSlot(int32 SaveNumber);
protected:
	UGameSaveSlotList* GetGameSaveSlotList();

protected:
	//存档
	UPROPERTY()
		UGameSaveSlotList* SlotList;

	//文件结构  GameState->GameSaveSlotList->SaveSlotList->FSaveSlot

};

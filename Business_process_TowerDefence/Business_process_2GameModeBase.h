// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Business_process_2GameModeBase.generated.h"


class ATowers;
class AMonster;
class ARuleOfTheCharacter;
class UDataTable;
//class ATowersDefencePlayerController;


/**
 * 
 */
UCLASS()
class BUSINESS_PROCESS_2_API ABusiness_process_2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
		/////////////////
public:
	ABusiness_process_2GameModeBase();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;


	//////生成角色

public:
	UFUNCTION(BlueprintCallable, Category = Sapwn)
		ATowers* SpawnTowers(int32 CharacterID, int32 CharacterLevel, const FVector& Loction, const FRotator& Rotator);
	UFUNCTION(BlueprintCallable, Category = Sapwn)
		AMonster* SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector& Loction, const FRotator& Rotator);
protected:
	ARuleOfTheCharacter* SpawnCharacter(int32 CharacterID, int32 CharacterLevel, UDataTable* InCharacterData, const FVector& Loction, const FRotator& Rotator, const FGuid& InCharacterGuid = FGuid());

	//生成角色并类型转换
	template<class T>
	T* SpawnCharacter(int32 CharacterID, int32 CharacterLevel, UDataTable* InCharacterData, const FVector& Loction, const FRotator& Rotator, const FGuid& InCharacterGuid = FGuid())
	{
		return Cast<T>(SpawnCharacter(CharacterID, CharacterLevel, InCharacterData, Loction, Rotator, InCharacterGuid));
	}
	//id +Guid生成
	/*ATowers* SpawnTowers(int32 CharacterID, const FVector& Loction, const FRotator& Rotator, const FGuid& InCharacterGuid);
	AMonster* SpawnMonster(int32 CharacterID, const FVector& Loction, const FRotator& Rotator, const FGuid& InCharacterGuid);*/
	


//protected:
//	void SpawnMainTowersRule();
//protected:
//	void InitDataFormArchives();
//	void InitData();
//protected:
//	void UpdateMonstersRule(float DeltaSeconds);

//	void UpdatePlayerData(float DeltaSeconds);

	void UpdateGameData(float DeltaSeconds);

//	void UpdatePlayerSkill(float DeltaSeconds);
//
//	void UpdateSkill(float DeltaSeconds);

	void UpdateInventory(float DeltaSeconds);








};
